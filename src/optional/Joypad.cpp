#include "Joypad.hpp"

init::Joypad::Joypad(init::MotionControl2D& motionController, const std::string &joypadTaskName): Base("Joypad"), motionController(motionController), raw2Motion(this, "raw2Motion"), joypad(this, joypadTaskName)
{

}

bool init::Joypad::connect()
{
    
    return init::Base::connect();
}
