#pragma once
#include "base_state.h"
#include "fsm.h"
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/Bool.h>

class search_cstation_state : public base_state
{
public:
    search_cstation_state(std::string name);
    void init(base_fsm *fsm, void *user_data) override;
    void enter(base_fsm *fsm, void *user_data) override;
    void update(base_fsm *fsm, void *user_data) override;
    void leave(base_fsm *fsm, void *user_data) override;
    void reset(base_fsm *fsm, void *user_data) override;

private:
    ros::Subscriber sub_reached_A_;
    ros::Publisher pub_goto_A_;
    geometry_msgs::PoseStamped cstation_pose_;
    geometry_msgs::PoseStamped A_pose_;
    ros::ServiceClient get_cstation_pose_client_;
    std::string reached_goal_tpcname_;
    bool whether_reached_A_;
    void get_A_pose(geometry_msgs::PoseStamped &pose); // 使用tf2库进行转换，还需要查询全局地图是否被占据。
    bool check_A_collision();                          // 碰撞检测
    void reached_goal_callback(const std_msgs::Bool::ConstPtr &msg);
};