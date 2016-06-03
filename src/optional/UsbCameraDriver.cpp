#include "UsbCameraDriver.hpp"

namespace init
{

UsbCameraDriver::UsbCameraDriver(const std::string& taskName): CameraDriver("UsbCameraDriver"), cameraTask(this, taskName)
{
    
}

OutputProxyPort< RTT::extras::ReadOnlyPointer< base::samples::frame::Frame > >& UsbCameraDriver::getFramePort()
{
    return cameraTask.getConcreteProxy()->frame;
}

}