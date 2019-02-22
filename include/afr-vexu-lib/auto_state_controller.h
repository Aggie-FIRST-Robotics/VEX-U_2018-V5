#ifndef VEX_U_2018_V5_AUTOSTATECONTROLLER_H
#define VEX_U_2018_V5_AUTOSTATECONTROLLER_H

#include "state_controller.h"

namespace AFR::VexU{
    class auto_state_controller : public state_controller{
        std::vector<std::function<state*()>> transitions;
        size_t current_index_;

    public:
        auto_state_controller(scheduled_update_t update_period, const std::vector<commandable*>& commandables,
                              const std::string& name) :
                state_controller(update_period, std::vector<state*>{}, commandables, nullptr, name), transitions(),
                current_index_(0){

        }

        state* add_state(const std::vector<action*>& actions, const std::function<void(state*)>& on_state_entry,
                         const std::string& name, const std::function<state*()>& transition_function){
            state* out = new state{actions, std::vector<transition>{}, on_state_entry, name};
            if(states_.empty()){
                current_state_ = out;
                current_state_->on_state_entry(current_state_);
            }
            states_.push_back(out);
            transitions.push_back(transition_function);
            return out;
        }

        void update_current_state() override{
            state* result = transitions.at(current_index_).operator()();
            if(result != nullptr){
                current_state_->on_state_exit(result);
                state* last = current_state_;
                current_state_ = result;
                current_index_ = find_state(result);
                result->on_state_entry(last);
            }
        }

        size_t find_state(state* state){
            for(size_t x = 0; x < states_.size(); x++){
                if(state == states_.at(x)){
                    return x;
                }
            }
            throw std::runtime_error{"Cannot find state: " + (state != nullptr ? state->get_name() : "null")};
        }
    };
}

#endif //VEX_U_2018_V5_AUTOSTATECONTROLLER_H
