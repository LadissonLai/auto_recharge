#include "back_vehicle_state.h"
#include <thread>

back_vehicle_state::back_vehicle_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void back_vehicle_state::init(base_fsm *fsm, void *user_data)
{
    initialized_ = true;
}

void back_vehicle_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter back_vehicle_state" << std::endl;
}

void back_vehicle_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave back_vehicle_state" << std::endl;
}

void back_vehicle_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void back_vehicle_state::reset(base_fsm *fsm, void *user_data)
{
}
