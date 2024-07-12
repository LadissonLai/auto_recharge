#pragma once
#include "base_state.h"
#include "fsm.h"
#include <ros/ros.h>

class dock_together_state : public base_state
{
public:
    dock_together_state(std::string name);
    void init(base_fsm *fsm, void *user_data) override;
    void enter(base_fsm *fsm, void *user_data) override;
    void update(base_fsm *fsm, void *user_data) override;
    void leave(base_fsm *fsm, void *user_data) override;
    void reset(base_fsm *fsm, void *user_data) override;

private:
    ros::Subscriber sub_;
};