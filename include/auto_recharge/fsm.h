#pragma once
#include "base_state.h"
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>  //exit函数
#include <typeinfo> //动态获取类名字
#include <cxxabi.h>
#include <ros/ros.h>

/* 辅助函数，用于去除名字修饰 */
std::string demangle(const char *mangled_name);

/**
 * 获取类名string
 * */
template <typename T>
static std::string get_type_name()
{
    return demangle(typeid(T).name()); // 返回类的名字
}

/* 有限状态机类 */
class base_fsm
{
private:
    base_state *curState_;
    std::map<std::string, base_state *> states_map_; // 使用字典维护这些新创建的状态，避免频繁的new和delete对象。
    bool ok_;
    ros::NodeHandle *nh_;

public:
    base_fsm() : curState_(nullptr), ok_(true) { states_map_.clear(); }
    ~base_fsm()
    {
        for (auto iter = states_map_.begin(); iter != states_map_.end(); iter++)
        {
            delete iter->second;
        }
        states_map_.clear();
        curState_ = nullptr;
    }

    template <typename T>
    void change_state(void *user_data = nullptr)
    {
        if (curState_)
        {
            curState_->leave(this, user_data);
        }
        std::string new_state_name = get_type_name<T>();
        std::map<std::string, base_state *>::iterator iter = states_map_.find(new_state_name);
        base_state *new_state;
        if (iter != states_map_.end()) // found
        {
            new_state = iter->second;
        }
        else // not found
        {
            new_state = new T(new_state_name);
            states_map_[new_state->get_name()] = new_state;
        }
        if (!new_state->initialized_)
        {
            new_state->init(this, user_data);
        }
        new_state->enter(this, user_data);
        this->curState_ = new_state;
    }

    template <typename T>
    void set_init_state(void *user_data = nullptr)
    {
        std::string init_state_name = get_type_name<T>();
        std::map<std::string, base_state *>::iterator iter = states_map_.find(init_state_name);
        if (iter != states_map_.end()) // found
        {
            this->curState_ = iter->second;
            if (!this->curState_->initialized_)
            {
                this->curState_->init(this, user_data);
            }
            this->curState_->enter(this, user_data);
        }
        else // not found
        {
            base_state *new_state = new T(init_state_name);
            states_map_[new_state->get_name()] = new_state;
            this->curState_ = new_state;
            new_state->init(this, user_data);
            new_state->enter(this, user_data);
        }
    }

    void update(void *user_data = nullptr)
    {
        if (curState_)
        {
            curState_->update(this, user_data);
        }
    }

    void reset(void *user_data = nullptr)
    {
        for (auto &iter : this->states_map_)
        {
            iter.second->reset(this, user_data);
        }
    }

    bool ok()
    {
        return ok_;
    }

    void set_ok()
    {
        this->ok_ = true;
    }

    void shutdown(void *user_data = nullptr)
    {
        this->ok_ = false;
        this->curState_->leave(this, user_data);
        this->curState_ = nullptr;
    }

    void set_node_handle(ros::NodeHandle *n)
    {
        this->nh_ = n;
    }

    ros::NodeHandle *get_node_handle()
    {
        return this->nh_;
    }
};