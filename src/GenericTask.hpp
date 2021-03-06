#pragma once

#include "Base.hpp"
#include "DependentTask.hpp"

namespace init
{
template<class T>
class GenericTask : public Base
{
public:
    GenericTask(const std::string& taskName) : Base(taskName), task(DependentTask<T>::getInstance(this, taskName))
    {
    }
    
    virtual ~GenericTask()
    {
    }
    
    DependentTask<T> task;
};

}
