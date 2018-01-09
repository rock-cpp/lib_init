#pragma once

#include <lib_init/IMUDriver.hpp>
#include <imu_xsens/proxies/TaskForward.hpp>
#include <lib_init/DependentTask.hpp>

namespace init
{

class IMUXsensDriver : public IMUDriver
{
    public:
        IMUXsensDriver(const std::string imuTaskName);
        virtual OutputProxyPort< base::samples::RigidBodyState > getOrientationSamples();
        virtual OutputProxyPort< base::samples::IMUSensors > getSensorSamples();
        bool estimate_bias(uint16_t seconds);

        virtual bool start();
        DependentTask<imu_xsens::proxies::Task> imuTask;
};

}


