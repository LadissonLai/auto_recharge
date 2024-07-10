#include "charged_state.h"
#include <iostream>
#include <thread>

charged_state::charged_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void charged_state::init(base_fsm *fsm, void *user_data)
{
}

void charged_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter charged_state" << std::endl;
}

void charged_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave charged_state" << std::endl;
}

void charged_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    fsm->shutdown();
}

void charged_state::reset(base_fsm *fsm, void *user_data)
{
}