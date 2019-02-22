#include "afr-vexu-lib/state_controller.h"

namespace AFR::VexU{
    void state_controller::update_private(const double& delta_seconds){
        update_current_state();
    };

    state_controller::state_controller(const scheduled_update_t& update_period, const std::vector<state*>& states,
                                       const std::vector<commandable*>& commandables, state* initial_state,
                                       const std::string& name) :
            readable(update_period, (initial_state != nullptr ? initial_state->get_name() : "null"), name),
            states_(states), commandables_(commandables), current_state_(initial_state){
        if(current_state_ != nullptr){
            current_state_->on_state_entry(current_state_);
        }
    }

    void AFR::VexU::state_controller::update_current_state(){
        if(current_state_ != nullptr){
            for(const auto& transition : current_state_->get_transitions()){
                if(transition.should_change_state()){
                    auto last_state = current_state_;
                    auto next_state = transition.get_next_state();
                    current_state_->on_state_exit(next_state);
                    current_state_ = next_state;
                    current_state_->on_state_entry(last_state);
                    value = current_state_->get_name();
                    break;
                }
            }
        }
        else{
            throw std::runtime_error{"Current state for " + get_name() + " is nullptr while updating current state"};
        }
    };

    void AFR::VexU::state_controller::update_actions(){
        if(current_state_ != nullptr){
            current_state_->update_actions();
        }
        else{
            throw std::runtime_error{"Current state for " + get_name() + " is nullptr while updating actions"};
        }
    };

    AFR::VexU::state* AFR::VexU::state_controller::get_state(const std::string& name){
        for(auto state : states_){
            if(state->get_name() == name){
                return state;
            }
        }
        return nullptr;
    };

    AFR::VexU::commandable* AFR::VexU::state_controller::get_commandable(const std::string& name){
        for(auto commandable : commandables_){
            if(commandable->get_name() == name){
                return commandable;
            }
        }
        return nullptr;
    }

    std::vector<state*>& state_controller::get_states(){
        return states_;
    }

    std::vector<commandable*>& state_controller::get_commandables(){
        return commandables_;
    }

    state* state_controller::get_current_state(){
        return current_state_;
    }
}
