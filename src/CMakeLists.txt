
# add_subdirectory(log_replay)

 
message("SRC extra is ${SRC_EXTRA}")
# message("HDR_EXTRA is ${HDR_EXTRA}")
# message("PKG_CONFIG_EXTRA is ${PKG_CONFIG_EXTRA}")

rock_library(lib_init
    SOURCES
        Base.cpp
        CommonStart.cpp
        DependentTask.cpp
        InitHelper.cpp
        MapProvider.cpp
        PointCloudProvider.cpp
        states/Init.cpp
        TransformerBroadcaster.cpp
        
        log_replay/CommonReplay.cpp
        log_replay/DepthMapProvider.cpp
        log_replay/DistanceImageProvider.cpp
        log_replay/ForceTorqueSensor.cpp
        log_replay/GenericRawToMotion2D.cpp
        log_replay/IMUDriver.cpp
        log_replay/JointDriver.cpp
        log_replay/ReplayTask.cpp
        log_replay/ReplayPort.cpp
        log_replay/PointCloudProvider.cpp
        log_replay/PositionProvider.cpp
        log_replay/TrajectoryFollower.cpp
    HEADERS
        Base.hpp
        CameraDriver.hpp
        Container.hpp
        CommonStart.hpp
        DependentTask.hpp
        ForceTorqueSensor.hpp
        GenericTask.hpp
        IMUDriver.hpp
        InitHelper.hpp
        JointDriver.hpp
        LaserDriver.hpp
        MapProvider.hpp
        DepthMapProvider.hpp
        DistanceImageProvider.hpp
        MotionControl2D.hpp
        MotionControl2DProvider.hpp
        MotionPlannerProvider.hpp
        PointCloudProvider.hpp
        PositionProvider.hpp
        TrajectoryControl.hpp
        states/Init.hpp
        TraversabilityMapProvider.hpp
        TransformerBroadcaster.hpp
        log_replay/CommonReplay.hpp
        log_replay/DepthMapProvider.hpp
        log_replay/DistanceImageProvider.hpp
        log_replay/ForceTorqueSensor.hpp
        log_replay/GenericRawToMotion2D.hpp
        log_replay/IMUDriver.hpp
        log_replay/JointDriver.hpp
        log_replay/ReplayTask.hpp
        log_replay/ReplayPort.hpp
        log_replay/PointCloudProvider.hpp
        log_replay/PositionProvider.hpp
        log_replay/TrajectoryFollower.hpp
    DEPS_PKGCONFIG
        base-lib
        orocos_cpp_base
        orocos_cpp
        lib_config
        logger-proxies
        logger-tasks-gnulinux
        state_machine
        state_machine_viz
        transformer-proxies
        lib_config
        rock_replay
)

