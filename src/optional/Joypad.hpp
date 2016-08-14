#pragma once

#include <lib_init/MotionControl2D.hpp>
#include <controldev/proxies/GenericRawToMotion2D.hpp>
#include <controldev/proxies/JoyPadTask.hpp>

namespace init {

class Joypad : public Base
{
protected:
    MotionControl2D &motionController;
    Joypad(MotionControl2D &motionController, const std::string &joypadTaskName);

    virtual bool connect();
    
    DependentTask<controldev::proxies::GenericRawToMotion2D> raw2Motion;
    DependentTask<controldev::proxies::JoyPadTask> joypad;
    
};
    
}
