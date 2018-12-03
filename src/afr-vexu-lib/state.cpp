#include "afr-vexu-lib/state.h"
#include <iostream>
#include <afr-vexu-lib/state.h>


AFR::VexU::state::state(const std::unordered_map<std::string, AFR::VexU::action&>& action_map,
                        const std::vector<AFR::VexU::transition>& transitions,
                        const std::function<error_t(const std::string&)>& on_state_entry, error_t* result)
        : action_map_(
        action_map),
          transitions_(transitions),
          on_state_entry_(
                                                                                                               on_state_entry){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::state::update_actions(){
    for(auto& action : action_map_){
        AFR_VEXU_INTERNAL_CALL(action.second.update());
    }
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::state::on_state_entry(const std::string& previous){
    for(auto& action : action_map_){
        action.second.on_state_entry(previous);
    }
    return on_state_entry_(previous);
}

AFR::VexU::error_t AFR::VexU::state::get_action(const std::string& identifier, action*& result){
    result = &action_map_.at(identifier);
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::state::get_transitions(const std::vector<transition>*& result){
    result = &transitions_;
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::state::on_state_exit(const std::string& next){
    for(auto& action : action_map_){
        action.second.on_state_exit(next);
    }
    return SUCCESS;
}

AFR::VexU::transition::transition(const std::function<error_t(bool&)>& condition_function,
                                  const std::string& next_state, error_t* result)
        : condition_function_(condition_function), next_state_(next_state){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::transition::should_change_state(bool& result) const{
    return condition_function_(result);
}

AFR::VexU::error_t AFR::VexU::transition::get_next_state(std::string& result) const{
    result = next_state_;
    return SUCCESS;
}
