#pragma once
#include <iostream>
#include <string>

class base_fsm;

class base_state
{
public:
    base_state() {}
    base_state(std::string n) { name_ = n; }
    ~base_state() {}
    virtual void init(base_fsm *fsm, void *user_data) = 0;
    virtual void enter(base_fsm *fsm, void *user_data) = 0;
    virtual void update(base_fsm *fsm, void *user_data) = 0;
    virtual void leave(base_fsm *fsm, void *user_data) = 0;
    virtual void reset(base_fsm *fsm, void *user_data) = 0;
    bool initialized_;
    std::string get_name() { return name_; }

protected:
    std::string name_;
};