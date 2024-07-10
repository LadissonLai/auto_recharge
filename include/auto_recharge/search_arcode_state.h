#pragma once
#include "base_state.h"
#include "fsm.h"
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

class seach_arcode_state : public base_state
{
public:
    seach_arcode_state(std::string name);
    void init(base_fsm *fsm, void *user_data) override;
    void enter(base_fsm *fsm, void *user_data) override;
    void update(base_fsm *fsm, void *user_data) override;
    void leave(base_fsm *fsm, void *user_data) override;
    void reset(base_fsm *fsm, void *user_data) override;

private:
    ros::Subscriber sub_reached_B_;
    ros::ServiceClient get_cstation_pose_client_;
    void get_B_pose(geometry_msgs::PoseStamped &pose);
};
