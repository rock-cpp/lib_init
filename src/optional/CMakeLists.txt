optional_init(hbridge-proxies 
    SOURCES
        HBridge.cpp    
    HEADERS
        HBridge.hpp    
)

optional_init(camera_usb-proxies
    SOURCES
        UsbCameraDriver.cpp
    HEADERS
        UsbCameraDriver.hpp
)

optional_init(canbus-proxies 
    SOURCES
        Canbus.cpp    
    HEADERS
        Canbus.hpp
)

optional_init(imu_xsens-proxies
    SOURCES
        IMUXsensDriver.cpp
    HEADERS
        IMUXsensDriver.hpp
)

optional_init(robot_frames-proxies
    SOURCES
        RobotFrames.cpp
    HEADERS
        RobotFrames.hpp
)

optional_init(mars-proxies
    SOURCES
        SimCameraDriver.cpp
        SimIMUDriver.cpp
        SimJointDriver.cpp
        SimLaserDriver.cpp
        Simulator.cpp
        SimVelodyneDriver.cpp
    HEADERS
        SimCameraDriver.hpp
        SimIMUDriver.hpp
        SimJointDriver.hpp
        SimLaserDriver.hpp
        Simulator.hpp
        SimVelodyneDriver.hpp
)

optional_init(odometry-proxies
    SOURCES
        SkidOdometry.cpp
    HEADERS
        SkidOdometry.hpp
)

optional_init(velodyne_lidar-proxies
    SOURCES
        VelodyneDriver.cpp
    HEADERS
        VelodyneDriver.hpp
)

optional_init(ndlcom_device_driver-proxies
    SOURCES
        NDLComJointDriver.cpp
    HEADERS
        NDLComJointDriver.hpp
)


optional_init(serial_ndlcom-proxies
    SOURCES
        NDLComSerial.cpp
    HEADERS
        NDLComSerial.hpp
)

optional_init(manipulator_motion_planner-proxies
    SOURCES
        ArmPlannerCartesianSpace.cpp
        ArmPlannerJointSpace.cpp
    HEADERS
        ArmPlanner.hpp
        ArmPlannerCartesianSpace.hpp
        ArmPlannerJointSpace.hpp
)

optional_init(tilt_scan-proxies
    SOURCES
        TiltScan.cpp
    HEADERS
        TiltScan.hpp
)

optional_init(projection-proxies
    SOURCES
        ColorizedPointcloud.cpp
    HEADERS
        ColorizedPointcloud.hpp
)


optional_init(hokuyo-proxies
    SOURCES
        HokuyoLaserDriver.cpp
    HEADERS
        HokuyoLaserDriver.hpp
)
optional_init(laser_filter-proxies)

optional_init(sb_object_detection-proxies
    SOURCES
        ObjectDetection.cpp
    HEADERS
        ObjectDetection.hpp
)

optional_init(graph_slam-proxies
    SOURCES
        VelodyneSlam.cpp
    HEADERS
        VelodyneSlam.hpp
)

optional_init(trajectory_follower-proxies
    SOURCES
        TrajectoryFollower.cpp
    HEADERS
        TrajectoryFollower.hpp
)

optional_init(servo_dynamixel-proxies
    SOURCES
        Dynamixel.cpp
    HEADERS
        Dynamixel.hpp
)

optional_init(motion_planning_libraries-proxies
    SOURCES
        MotionPlanner.cpp
    HEADERS
        MotionPlanner.hpp
)

optional_init(localization-proxies
    SOURCES
        PoseProvider.cpp
    HEADERS
        PoseProvider.hpp
)

optional_init(traversability-proxies
    SOURCES
        TraversabilitySimple.cpp
    HEADERS
        TraversabilitySimple.hpp
)

optional_init(wbc-proxies
    SOURCES
        WholeBodyControl.cpp
    HEADERS
        WholeBodyControl.hpp
)
optional_init(kccd-proxies)
optional_init(ctrl_lib-proxies)
optional_init(waypoint_provider-proxies)


optional_init(trajectory_generation-proxies
    SOURCES
        TrajectoryGeneration.cpp
        TrajectoryGenerationVelocity.cpp
    HEADERS
        TrajectoryGeneration.hpp
        TrajectoryGenerationVelocity.hpp
)


optional_init(pgpg_sampler-proxies
    SOURCES
        PGPGSampler.cpp
    HEADERS
        PGPGSampler.hpp
)
