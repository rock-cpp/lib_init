#include "DependentTask.hpp"
#include "Base.hpp"
#include <stdexcept>
#include <orocos_cpp/Deployment.hpp>
#include <rtt/transports/corba/TaskContextProxy.hpp>

namespace init 
{

DependentTaskBase::DependentTaskBase(Base *parent, const std::string &taskName, const std::string &taskModelName) : taskName(taskName), taskModel(taskModelName), proxy(nullptr)
{
    config.push_back("default");

    deployment.reset(new orocos_cpp::Deployment(taskModel, taskName));
    parent->registerTask(this);
}

DependentTaskBase::~DependentTaskBase()
{

}

RTT::corba::TaskContextProxy* DependentTaskBase::getProxy()
{
    if(!proxy)
    {
        proxy = RTT::corba::TaskContextProxy::Create(taskName, false);
    }
    
    return proxy;
}

void DependentTaskBase::setName(const std::string& newName)
{
    if(proxy)
        throw std::runtime_error("init::DependentTaskBase::setName : Error name set after proxy was initialized");

    taskName = newName;
    deployment->renameTask(prefix + taskName, prefix + newName);
}

void DependentTaskBase::setPrefix(const std::string& newPrefix)
{
    if(!prefix.empty())
        throw std::runtime_error("init::DependentTaskBase::setPrefix : Error prefix already set, double call is not allowed");
    
    if(proxy)
        throw std::runtime_error("init::DependentTaskBase::setPrefix : Error prefix set after proxy was initialized");

    //check if this deployment is shared, and someone else already 
    //renamed the logger
    if(deployment->getLoggerName().find(newPrefix) == std::string::npos)
    {
        deployment->renameTask(prefix + deployment->getLoggerName(), newPrefix + deployment->getLoggerName());
    };
    
    deployment->renameTask(prefix + taskName, newPrefix + taskName);

    prefix = newPrefix;    
    
    //for full second prefix support remove prefix config here...
    config.push_back(prefix);
}

void DependentTaskBase::setDeployment(const std::shared_ptr< orocos_cpp::Deployment >& newDeployment)
{
    if(!prefix.empty())
        throw std::runtime_error("init::DependentTaskBase::setDeployment: error, setting deployment, after setting of prefix is not allowed");
    
    if(!newDeployment)
        throw std::runtime_error("init::DependentTaskBase::setDeployment: Error, deployment contains nullptr");
    
    deployment = newDeployment;
    
    //check if our task name is present in the deployment
    const auto taskNames = deployment->getTaskNames();
    if(std::find(taskNames.begin(), taskNames.end(), getTaskName()) == taskNames.end())
        throw std::runtime_error("init::DependentTaskBase::setDeployment: error, task name " + getTaskName() + " was not found in deployment " + deployment->getName());
}

void DependentTaskBase::setConfig(const std::vector< std::string >& configs)
{
    config = configs;
}

void DependentTaskBase::setConfig(const std::string& config1)
{
    config.clear();
    
    config.push_back(config1);
}

void DependentTaskBase::setConfig(const std::string& config1, const std::string& config2)
{
    config.clear();
    
    config.push_back(config1);
    config.push_back(config2);
}

void DependentTaskBase::setConfig(const std::string& config1, const std::string& config2, const std::string& config3)
{
    config.clear();
    
    config.push_back(config1);
    config.push_back(config2);
    config.push_back(config3);
}


}