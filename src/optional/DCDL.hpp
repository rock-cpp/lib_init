#pragma once

#include <lib_init/Base.hpp>
#include <dcdl/proxies/DifferentialClassifier.hpp>
#include <dcdl/proxies/IMUClassifier.hpp>
#include <dcdl/proxies/TrajectoryClassifier.hpp>
#include <dcdl/proxies/EnsembleClassifier.hpp>
#include <lib_init/IMUDriver.hpp>
#include <lib_init/MotionControl2DProvider.hpp>
#include "TrajectoryFollower.hpp"
#include <lib_init/PositionProvider.hpp>

namespace init
{
 
class DCDL : public Base
{
    
    TrajectoryFollower &trajectoryFollower;
    PositionProvider &poseProvider;
    IMUDriver &imu;
 
public:
    DCDL(const std::string trajClassifierName, const std::string diffClassifierName, const std::string imuClassifierName,
         TrajectoryFollower &trajectoryFollower, PositionProvider &poseProvider, IMUDriver &imu);
    ~DCDL() = default;
    
    virtual bool connect();
    DependentTask<dcdl::proxies::TrajectoryClassifier> trajectoryClassifierTask;
    DependentTask<dcdl::proxies::DifferentialClassifier> differentialClassifierTask;    
    DependentTask<dcdl::proxies::IMUClassifier> imuClassifierTask;
};



class DCDLEnsemble : public MotionControl2DProvider
{
    DCDL &dcdl;
    PositionProvider &poseProvider;
    
public:
    DCDLEnsemble(const std::string taskName, DCDL &dcdl, PositionProvider &poseProvider);
    ~DCDLEnsemble() = default;
    
    virtual bool connect();
    virtual OutputProxyPort<base::commands::Motion2D> &getCommand2DPort();
    DependentTask<dcdl::proxies::EnsembleClassifier> ensembleClassifierTask;
};
    
}