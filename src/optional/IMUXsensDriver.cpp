#include "IMUXsensDriver.hpp"
#include <imu_xsens/proxies/Task.hpp>

init::IMUXsensDriver::IMUXsensDriver(const std::string imuTaskName) : Base("IMUXsensDriver"), IMUDriver("IMUXsensDriver")
    , imuTask(DependentTask<imu_xsens::proxies::Task>::getInstance(this, imuTaskName))
{
}

bool init::IMUXsensDriver::start()
{
    if(!init::Base::start())
        return false;
    
    std::cout << getName() << ": Estimating IMU bias for 3 seconds" << std::endl;
    return estimate_bias(3);
}


OutputProxyPort< base::samples::RigidBodyState > init::IMUXsensDriver::getOrientationSamples()
{
    return imuTask.getConcreteProxy()->orientation_samples;
}

OutputProxyPort< base::samples::IMUSensors > init::IMUXsensDriver::getSensorSamples()
{
    return imuTask.getConcreteProxy()->calibrated_sensors;
}


bool init::IMUXsensDriver::estimate_bias(uint16_t seconds)
{
    return imuTask.getConcreteProxy()->estimate_bias(seconds);
}
