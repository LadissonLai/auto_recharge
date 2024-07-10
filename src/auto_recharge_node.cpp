/**
 * 自动回充功能：状态间切换维护。
 */

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "fsm.h"
#include "search_cstation_state.h"

double battery_remains;
bool use_low_battery = false;
void low_battery_callback(const std_msgs::Int32::ConstPtr &msg)
{
    use_low_battery = true;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "auto_recharge");
    ros::NodeHandle private_nh("~");
    ros::NodeHandle private_nh_state("~");
    std::string low_battery_topic;
    private_nh.param<std::string>("low_battery_topic", low_battery_topic, "low_battery");
    ros::Subscriber sub_low_battery = private_nh.subscribe(low_battery_topic, 1, low_battery_callback);
    // sub_low_battery.shutdown();
    base_fsm fsm;
    fsm.set_node_handle(&private_nh_state);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        if (use_low_battery)
        {
            fsm.set_init_state<search_cstation_state>();
            while (fsm.ok())
            {
                fsm.update();
            }
            use_low_battery = false;
            fsm.set_ok();
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}