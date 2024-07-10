#include "base_state.h"

base_state::base_state(std::string n)
{
    name_ = n;
}

void base_state::init(base_fsm *fsm, void *user_data)
{
    this->initialized_ = true;
    std::cout << "init " << this->name_ << std::endl;
}

void base_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "---enter " << this->name_ << std::endl;
}

void base_state::update(base_fsm *fsm, void *user_data)
{
    std::cout << "update " << this->name_ << std::endl;
}

void base_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "---leave " << this->name_ << std::endl;
}

void base_state::reset(base_fsm *fsm, void *user_data)
{
    std::cout << "---leave " << this->name_ << std::endl;
}