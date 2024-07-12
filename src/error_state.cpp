#include "error_state.h"
#include <thread>

error_state::error_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void error_state::init(base_fsm *fsm, void *user_data)
{
    initialized_ = true;
}

void error_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter error_state" << std::endl;
}

void error_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave error_state" << std::endl;
}

void error_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void error_state::reset(base_fsm *fsm, void *user_data)
{
}