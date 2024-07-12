#include "dock_together_state.h"
#include <thread>

dock_together_state::dock_together_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void dock_together_state::init(base_fsm *fsm, void *user_data)
{
    initialized_ = true;
}

void dock_together_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter dock_together_state" << std::endl;
}

void dock_together_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave dock_together_state" << std::endl;
}

void dock_together_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void dock_together_state::reset(base_fsm *fsm, void *user_data)
{
}