/**
 * 更新充电桩的位置。
 *
 * */

#include <iostream>
#include <ros/ros.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <geometry_msgs/Pose.h>

class UpdateCStationPose
{
public:
    UpdateCStationPose() : private_nh_("~")
    {
        private_nh_.param<std::string>("cstation_pose_file", cstation_pose_file_, "");
        private_nh_.param<std::string>("update_cstation_pose_topic", update_cstation_pose_topic, "/update_cstation_pose");
        load_yaml_file(cstation_pose_file_, pose_config_);
        // 订阅充电桩位置更新话题
        ros::Subscriber sub_update_pose_ = private_nh_.subscribe(update_cstation_pose_topic, 1, updatePoseCallback, this);
    }
    void run() {}

private:
    ros::NodeHandle private_nh_;
    std::string cstation_pose_file_;
    YAML::Node pose_config_;
    ros::Subscriber sub_update_pose_;
    std::string update_cstation_pose_topic;

    bool fileExists(const std::string &filename)
    {
        std::ifstream file(filename);
        return file.good();
    }

    void load_yaml_file(const std::string &file_path, YAML::Node &config)
    {
        // 检查文件是否存在
        if (!fileExists(file_path))
        {
            config["saved"] = false;
            config["location"] = YAML::Node(YAML::NodeType::Map);
            config["location"]["x"] = 0.0;
            config["location"]["y"] = 0.0;
            config["location"]["z"] = 0.0;
            config["rotation"] = YAML::Node(YAML::NodeType::Map);
            config["rotation"]["x"] = 0.0;
            config["rotation"]["y"] = 0.0;
            config["rotation"]["z"] = 0.0;
            std::ofstream fout(file_path);
            fout << config;
        }
        else
        {
            config = YAML::LoadFile(file_path);
        }
    }

    void updatePoseCallback(const geometry_msgs::Pose::ConstPtr &msg)
    {
        ROS_INFO("I heard: [%s]", msg->position);
        if (!this->pose_config_["saved"])
        {
            this->pose_config_["saved"] = true;
        }
        pose_config_["location"]["x"] = msg->position.x;
        pose_config_["location"]["y"] = msg->position.y;
        pose_config_["location"]["z"] = msg->position.z;
    }
};

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "update_cstation_pose_node");
    UpdateCStationPose upCStation;
    upCStation.run();
    ros::spin();
    return 0;
}