#include "search_arcode_state.h"
#include "charged_state.h"
#include <iostream>
#include <thread>

seach_arcode_state::seach_arcode_state(std::string name)
{
    name_ = name;
    initialized_ = false;
}

void seach_arcode_state::init(base_fsm *fsm, void *user_data)
{
}

void seach_arcode_state::enter(base_fsm *fsm, void *user_data)
{
    std::cout << "enter seach_arcode_state" << std::endl;
}

void seach_arcode_state::leave(base_fsm *fsm, void *user_data)
{
    std::cout << "leave seach_arcode_state" << std::endl;
}

void seach_arcode_state::update(base_fsm *fsm, void *user_data)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    fsm->change_state<charged_state>();
}

void seach_arcode_state::reset(base_fsm *fsm, void *user_data)
{
}