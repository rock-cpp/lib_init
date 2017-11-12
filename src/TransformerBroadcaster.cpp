#include "TransformerBroadcaster.hpp"
#include <transformer/proxies/Task.hpp>

namespace init {
TransformerBroadcaster::TransformerBroadcaster(const std::string &taskName, const smurf::Robot &robot): 
    Base("TransformerBroadcaster"),
    robot(robot),
    broadcaster(this, taskName, new DependentTaskPimplImpl<transformer::proxies::Task>())
{

}

bool TransformerBroadcaster::start()
{
    if(!init::Base::start())
        return false;
    
    //set transformations
    transformer::ConfigurationState state;

    state.static_transformations.reserve(robot.getStaticTransforms().size());
    
    for(smurf::StaticTransformation *t : robot.getStaticTransforms())
    {
        base::samples::RigidBodyState rbs;
        // NOTE: In the smurf loader classes source and target frame is interpreted the other way around. The transformation however is the same.
        rbs.sourceFrame = t->getTargetFrame().getName();
        rbs.targetFrame = t->getSourceFrame().getName();
        rbs.setTransform(t->getTransformation());
        
        state.static_transformations.push_back(rbs);
    }

    state.port_transformation_associations.reserve(robot.getDynamicTransforms().size());
    for(smurf::DynamicTransformation *t : robot.getDynamicTransforms())
    {
        transformer::PortTransformationAssociation a;
        // NOTE: In the smurf loader classes source and target frame is interpreted the other way around.
        a.from_frame = t->getTargetFrame().getName();
        a.to_frame = t->getSourceFrame().getName();
        a.task = t->getProviderName();
        a.port = t->getProviderPortName();
        
        state.port_transformation_associations.push_back(a);
    }

    broadcaster.getConcreteProxy()->setConfiguration(state);
    
    return true;
}

    
}
