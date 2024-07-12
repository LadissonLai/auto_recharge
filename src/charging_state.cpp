#include "charging_state.h"
#include <thread>

charging_state::charging_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void charging_state::init(base_fsm *fsm, void *user_data)
{
    initialized_ = true;
}

void charging_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter charging_state" << std::endl;
}

void charging_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave charging_state" << std::endl;
}

void charging_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void charging_state::reset(base_fsm *fsm, void *user_data)
{
}