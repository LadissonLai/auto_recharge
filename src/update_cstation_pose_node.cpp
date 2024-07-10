/**
 * 更新充电桩的位置，并保存在yaml文件中。
 * 还需要提供一个service，获取充电桩的位姿。
 * */

#include <iostream>
#include <ros/ros.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

class UpdateCStationPose
{
public:
    UpdateCStationPose() : private_nh_("~")
    {
        private_nh_.param<std::string>("cstation_pose_file", cstation_pose_file_, "");
        private_nh_.param<std::string>("update_cstation_pose_topic", update_cstation_pose_topic_, "/update_cstation_pose");
        private_nh_.param<std::string>("frame_name", frame_name_, "map");
        load_yaml_file(cstation_pose_file_, pose_config_);
        // 订阅充电桩位置更新话题
        sub_update_pose_ = private_nh_.subscribe(update_cstation_pose_topic_, 1, &UpdateCStationPose::updatePoseCallback, this);
    }
    void run() {}

private:
    ros::NodeHandle private_nh_;
    std::string cstation_pose_file_;
    YAML::Node pose_config_;
    std::string update_cstation_pose_topic_;
    std::string frame_name_;
    ros::Subscriber sub_update_pose_;

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
            ROS_INFO("[%s]: create cstation yaml file successful..", ros::this_node::getName().c_str());
        }
        else
        {
            config = YAML::LoadFile(file_path);
        }
    }

    void updatePoseCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        // ROS_INFO("I heard: [%f]", msg->pose.position.x);
        if (msg->header.frame_id != this->frame_name_)
        {
            return;
        }
        this->pose_config_["saved"] = true;
        pose_config_["location"]["x"] = msg->pose.position.x;
        pose_config_["location"]["y"] = msg->pose.position.y;
        pose_config_["location"]["z"] = msg->pose.position.z;
        // 四元数转欧拉角
        tf2::Quaternion qtn;
        double roll, pitch, yaw;
        tf2::fromMsg(msg->pose.orientation, qtn);
        tf2::Matrix3x3 m(qtn);
        m.getRPY(roll, pitch, yaw);
        pose_config_["rotation"]["x"] = roll;
        pose_config_["rotation"]["y"] = pitch;
        pose_config_["rotation"]["z"] = yaw;
        // 保存yaml文件
        std::ofstream outf(this->cstation_pose_file_);
        outf << pose_config_;
        outf.close();
        return;
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