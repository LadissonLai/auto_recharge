#pragma once
#include <iostream>
#include <string>

class base_fsm;

class base_state
{
public:
    base_state(){};
    base_state(std::string);
    ~base_state(){};
    virtual void init(base_fsm *fsm, void *user_data);
    virtual void enter(base_fsm *fsm, void *user_data);
    virtual void update(base_fsm *fsm, void *user_data);
    virtual void leave(base_fsm *fsm, void *user_data);
    virtual void reset(base_fsm *fsm, void *user_data);
    bool initialized_;
    std::string get_name() { return name_; }

protected:
    std::string name_;
};