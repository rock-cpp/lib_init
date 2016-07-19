#pragma once

#include <lib_init/PositionProvider.hpp>
#include <odometry/proxies/LatOdom.hpp>
#include <lib_init/JointDriver.hpp>
#include <lib_init/IMUDriver.hpp>

namespace init
{

class LateralOdometry : public PositionProvider
{
    JointDriver &joints;
    IMUDriver &imu;
public:
    LateralOdometry(const std::string &odometryName, JointDriver &joints, IMUDriver &imu);
    virtual ~LateralOdometry();
    virtual bool connect();
    DependentTask<odometry::proxies::LatOdom> lateralOdometry;
    
    virtual OutputProxyPort< base::samples::RigidBodyState >& getPositionSamples();
};

}

