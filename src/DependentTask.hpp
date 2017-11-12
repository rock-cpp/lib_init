#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace RTT {
    namespace corba {
        class TaskContextProxy;
    }
}

namespace orocos_cpp {
    class Deployment;
}

namespace init {

class Base;
    
class DependentTaskBase
{
protected:
    std::string taskName;
    std::string taskModel;
    std::string prefix;
    boost::shared_ptr<orocos_cpp::Deployment> deployment;
    std::vector<std::string> config;

    RTT::corba::TaskContextProxy *proxy;
public:
    DependentTaskBase(Base *parent, const std::string &taskName, const std::string &taskModelName);
    
    virtual ~DependentTaskBase();
    
    const std::string getTaskName() const
    {
        return prefix + taskName;
    }

    const std::string &getModelName() const
    {
        return taskModel;
    }
    
    void setPrefix(const std::string &name);
    
    const std::string &getPrefix() const
    {
        return prefix;
    }

    void setName(const std::string &newName);
    
    void setDeployment(const boost::shared_ptr<orocos_cpp::Deployment> &newDeployment);

    const boost::shared_ptr<orocos_cpp::Deployment> &getDeployment() const
    {
        return deployment;
    }
    
    const std::vector<std::string> &getConfig() const 
    {
        return config;
    }
    
    void setConfig(const std::vector<std::string> &configs);
    void setConfig(const std::string &config);
    void setConfig(const std::string &config, const std::string &config2);
    void setConfig(const std::string& config, const std::string& config2, const std::string& config3);

    
    virtual RTT::corba::TaskContextProxy *getProxy();
    
};
    
class DependentTaskPimplBase
{
public:
    virtual ~DependentTaskPimplBase() {};
    virtual const std::string &getModelName() = 0;
    virtual RTT::corba::TaskContextProxy* createProxy(const std::string &name) = 0;;
};

template <class TASK>
class DependentTaskPimplImpl : public DependentTaskPimplBase
{
public:
    DependentTaskPimplImpl();
    virtual ~DependentTaskPimplImpl() {};
    virtual const std::string &getModelName()
    {
        return TASK::ModelName;
    }
    
    virtual RTT::corba::TaskContextProxy* createProxy(const std::string &name)
    {
        return TASK(name);
    }
};

template <class TASK>
class DependentTask : public DependentTaskBase
{
    DependentTaskPimplBase *pimpl;
public:    
    DependentTask(Base *parent, const std::string &taskName, DependentTaskPimplBase *pimpl) : DependentTaskBase(parent, taskName, pimpl->getModelName())
    {
    }
    
    virtual RTT::corba::TaskContextProxy* getProxy()
    {
        if(!proxy)
            proxy = pimpl->createProxy(prefix + taskName);
        
        //std::cout << "Got proxy for " << proxy->getName() << " local name " << prefix + taskName  << "( " << getModelName() << " )" << std::endl;

        return proxy;
    };
    
    static DependentTask<TASK> getInstance(Base *parent, const std::string &taskName)
    {
        return DependentTask(parent, taskName, new DependentTaskPimplImpl<TASK>());
    }
    
    TASK* getConcreteProxy()
    {
        if(!proxy)
            getProxy();

        return dynamic_cast<TASK *>(proxy);
    };
    
    
    
    
};
    
    
}