
#include <afr-vexu-lib/state_controller.h>

namespace AFR::VexU{
    void state_controller::update_private(const double& delta_seconds){
        update_current_state();
    };

    state_controller::state_controller(const scheduled_update_t& update_period, const std::vector<state*>& state_map,
                                       const std::vector<commandable*>& commandable_map, state* initial_state,
                                       const std::string& name)
            : scheduled(update_period), nameable(name), states_(state_map), commandables_(commandable_map),
              current_state_(initial_state){
        current_state_->on_state_entry(current_state_);
    }

    void AFR::VexU::state_controller::update_current_state(){
        for(const auto& transition : current_state_->get_transitions()){
            if(transition.should_change_state()){
                auto last_state = current_state_;
                auto next_state = transition.get_next_state();
                current_state_->on_state_exit(next_state);
                current_state_ = next_state;
                current_state_->on_state_entry(last_state);
                break;
            }
        }
    };

    void AFR::VexU::state_controller::update_actions(){
        current_state_->update_actions();
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
}
