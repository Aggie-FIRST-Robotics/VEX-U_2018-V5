#include "afr-vexu-lib/state.h"

namespace AFR::VexU{
    state::state(const std::vector<action*>& action_map, const std::vector<transition>& transitions,
                 const std::function<void(state*)>& on_state_entry, const std::string& name)
            : nameable(name), actions_(action_map), transitions_(transitions), on_state_entry_(on_state_entry){}

    void state::update_actions(){
        for(auto action : actions_){
            action->update();
        }
    }

    void AFR::VexU::state::on_state_entry(state* previous){
        for(auto action : actions_){
            action->on_state_entry(previous);
        }
        on_state_entry_(previous);
    }

    action* AFR::VexU::state::get_action(const std::string& name){
        for(auto action : actions_){
            if(action->get_name() == name){
                return action;
            }
        }
        return nullptr;
    }

    std::vector<transition>& AFR::VexU::state::get_transitions(){
        return transitions_;
    }

    void AFR::VexU::state::on_state_exit(state* next){
        for(auto action : actions_){
            action->on_state_exit(next);
        }
    }

    std::vector<action*>& state::get_actions(){
        return actions_;
    }

    transition::transition(const std::function<bool()>& condition_function, state*& next_state,
                           const std::string& name)
            : nameable(name), condition_function_(condition_function), next_state_(next_state){
    }

    bool transition::should_change_state() const{
        return condition_function_();
    }

    state* transition::get_next_state() const{
        return next_state_;
    }
}
