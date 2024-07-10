#include "search_cstation_state.h"
#include "search_arcode_state.h"
#include <thread>

search_cstation_state::search_cstation_state(std::string n)
{
    name_ = n;
    initialized_ = false;
}

void search_cstation_state::init(base_fsm *fsm, void *user_data)
{
    initialized_ = true;
    fsm->get_node_handle()->param<std::string>("reached_goal", reached_goal_tpcname_, "reached_goal");
}

void search_cstation_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter search_cstation_state" << std::endl;
    whether_reached_A_ = false;
    // sub_reached_A_ = fsm->get_node_handle()->subscribe(reached_goal_tpcname_, 2, &search_cstation_state::reached_goal_callback, this);
}

void search_cstation_state::leave(base_fsm *fsm, void *user_data)
{
    sub_reached_A_.shutdown();
    std::cout << "leave search_cstation_state" << std::endl;
}

void search_cstation_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    fsm->change_state<seach_arcode_state>();
}

void search_cstation_state::reset(base_fsm *fsm, void *user_data)
{
}

void search_cstation_state::get_A_pose(geometry_msgs::PoseStamped &pose)
{
    geometry_msgs::PoseStamped p;
    pose.header = p.header;
    pose.pose = p.pose;
}