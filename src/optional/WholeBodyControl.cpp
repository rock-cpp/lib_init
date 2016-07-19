#include "WholeBodyControl.hpp"
#include <wbc/proxies/WbcVelocityTask.hpp>
#include <ctrl_lib/proxies/CartesianPositionController.hpp>
#include <ctrl_lib/proxies/JointPositionController.hpp>
#include <kccd/proxies/SelfCollisionCheck.hpp>
#include <kccd/proxies/SelfCollisionCtrl.hpp>
#include <waypoint_provider/proxies/JointWaypointProviderTrajectoryInput.hpp>

namespace init 
{
    
WholeBodyControl::WholeBodyControl(TrajectoryControl& trajCtrl,
                                   const std::string& wbcTaskName, 
                                   const std::string& cartPosCtrlTaskName, 
                                   const std::string& jointPosCtrlTaskName,
                                   const std::string& kccdCheckTaskName,
                                   const std::string& kccdCtrlTaskName,
                                   const std::string& waypointProvTaskName) 
    : Base("WholeBodyControl")
    , trajCtrl(trajCtrl)
    , wbcTask(this, wbcTaskName)
    , cartPosCtrlTask(this, cartPosCtrlTaskName)
    , jointPosCtrlTask(this, jointPosCtrlTaskName)
    , kccdCheckTask(this, kccdCheckTaskName)
    , kccdCtrlTask(this, kccdCtrlTaskName)
    , waypointProvTask(this, waypointProvTaskName)
    { 
        registerDependency(trajCtrl);
    }

    
bool WholeBodyControl::connect()
{
    waypointProvTask.getConcreteProxy()->current_target.connectTo(jointPosCtrlTask.getConcreteProxy()->setpoint);
    
    wbcTask.getConcreteProxy()->ctrl_out.connectTo(kccdCtrlTask.getConcreteProxy()->command);
//     TrajectoryGenerationVelocity *traj = (TrajectoryGenerationVelocity*) &trajCtrl;
//     wbcTask.getConcreteProxy()->ctrl_out.connectTo(traj->getVelocityTargetPort());
    kccdCheckTask.getConcreteProxy()->collision_info.connectTo(kccdCtrlTask.getConcreteProxy()->collision_info);
    trajCtrl.getJointStatusPort().connectTo(kccdCtrlTask.getConcreteProxy()->joint_state);

    
    trajCtrl.getJointStatusPort().connectTo(jointPosCtrlTask.getConcreteProxy()->feedback);
    trajCtrl.getJointStatusPort().connectTo(wbcTask.getConcreteProxy()->joint_state);
    trajCtrl.getJointStatusPort().connectTo(waypointProvTask.getConcreteProxy()->current_position);
    trajCtrl.getJointStatusPort().connectTo(kccdCheckTask.getConcreteProxy()->joint_state);
    
    return true;
}

bool WholeBodyControl::configure()
{
    
    bool ret = init::Base::configure();
    if(!ret)
        return ret;
    
    wbcTask.getConcreteProxy()->synchronize();
    
    RTT::base::PortInterface *ref_joint_pos_ctrl = wbcTask.getConcreteProxy()->getPort("ref_joint_pos_ctrl");
    RTT::base::PortInterface *activation_joint_pos_ctrl = wbcTask.getConcreteProxy()->getPort("activation_joint_pos_ctrl");
    RTT::base::PortInterface *ref_cart_pos_ctrl = wbcTask.getConcreteProxy()->getPort("ref_cart_pos_ctrl");
    RTT::base::PortInterface *activation_cart_pos_ctrl = wbcTask.getConcreteProxy()->getPort("activation_cart_pos_ctrl");
    RTT::base::PortInterface *pose_cart_pos_ctrl = wbcTask.getConcreteProxy()->getPort("pose_cart_pos_ctrl");
    RTT::base::PortInterface *joint_state_collision = wbcTask.getConcreteProxy()->getPort("joint_state_joint_pos_ctrl");
  
    if(!ref_joint_pos_ctrl)
        throw std::runtime_error("WholeBodyControl:: Error, wbc has no port ref_joint_pos_ctrl. Needs to be configured");
    if(!ref_cart_pos_ctrl)
        throw std::runtime_error("WholeBodyControl:: Error, wbc has no port ref_cart_pos_ctrl. Needs to be configured");
    if(!pose_cart_pos_ctrl)
        throw std::runtime_error("WholeBodyControl:: Error, wbc has no port pose_cart_pos_ctrl. Needs to be configured");
    if(!joint_state_collision)
        throw std::runtime_error("WholeBodyControl:: Error, wbc has no port joint_state_collision. Needs to be configured");
    
    jointPosCtrlTask.getConcreteProxy()->control_output.getPortInterface()->connectTo(ref_joint_pos_ctrl);
//     jointPosCtrlTask.getConcreteProxy()->activation.getPortInterface()->connectTo(activation_joint_pos_ctrl);
    cartPosCtrlTask.getConcreteProxy()->control_output.getPortInterface()->connectTo(ref_cart_pos_ctrl);
//     cartPosCtrlTask.getConcreteProxy()->activation.getPortInterface()->connectTo(activation_cart_pos_ctrl);
    
    pose_cart_pos_ctrl->connectTo(cartPosCtrlTask.getConcreteProxy()->feedback.getPortInterface());

    joint_state_collision->connectTo(kccdCheckTask.getConcreteProxy()->joint_state.getPortInterface());

    return ret;
}

InputProxyPort< base::samples::Joints >& WholeBodyControl::getPositionTargetPort()
{
    return jointPosCtrlTask.getConcreteProxy()->setpoint;
}

InputProxyPort< base::JointsTrajectory >& WholeBodyControl::getTrajectoryTargetPort()
{
    return waypointProvTask.getConcreteProxy()->waypoints_in;
}

InputProxyPort< base::samples::RigidBodyState >& WholeBodyControl::getCartPosTargetPort()
{
    return cartPosCtrlTask.getConcreteProxy()->setpoint;
}

OutputProxyPort< base::samples::Joints > WholeBodyControl::getCommandOutPort()
{
    return wbcTask.getConcreteProxy()->ctrl_out;
}

OutputProxyPort< trajectory_generation::ConstrainedJointsCmd >& WholeBodyControl::getConstrainedCommandOutPort()
{
    return kccdCtrlTask.getConcreteProxy()->constrained_command_out;
}


}