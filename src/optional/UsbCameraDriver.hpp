#pragma once

#include <lib_init/CameraDriver.hpp>
#include <camera_usb/proxies/Task.hpp>

namespace camera_usb {
 namespace proxies {
     class Task;
 }
}

namespace init 
{
class UsbCameraDriver : public CameraDriver
{
public: 
    UsbCameraDriver(const std::string &taskName);
    
    virtual OutputProxyPort< RTT::extras::ReadOnlyPointer< base::samples::frame::Frame > > &getFramePort();
    
    DependentTask<camera_usb::proxies::Task> cameraTask;
};
}