#include "TrajectoryFollower.hpp"

namespace log_replay
{
    
TrajectoryFollower::TrajectoryFollower(const std::string& taskName, const std::string& followerDataPortName) 
    : Base("TrajectoryFollowerReplay")
    , task(this, taskName)
    , followerDataPort(task, followerDataPortName)
{

}

OutputProxyPort< trajectory_follower::FollowerData >& TrajectoryFollower::getFollowerData()
{
    return followerDataPort.getPort();
}

    
}