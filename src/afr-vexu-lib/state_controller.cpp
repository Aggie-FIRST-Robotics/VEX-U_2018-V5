#include "afr-vexu-lib/state_controller.h"

AFR::VexU::error_t AFR::VexU::state_controller::update_private(const double& delta_seconds){
    return update_current_state();
};

AFR::VexU::state_controller::state_controller(const scheduled_update_t& update_period,
                                              const std::unordered_map<std::string, AFR::VexU::state&>& state_map,
                                              const std::unordered_map<std::string, AFR::VexU::commandable&>& commandable_map,
                                              const std::string& initial_state, error_t* result) : scheduled(
        update_period, result),
                                                                                                   state_map_(
                                                                                                           state_map),
                                                                                                   commandable_map_(
                                                                                                           commandable_map),
                                                                                                   current_state_(
                                                                                                           &state_map.at(
                                                                                          initial_state)){
    if(result != nullptr && *result == SUCCESS){
        *result = current_state_->on_state_entry(*current_state_);
    }
    else if(result == nullptr){
        current_state_->on_state_entry(*current_state_);
    }
}

AFR::VexU::error_t AFR::VexU::state_controller::update_current_state(){
    const std::vector<transition>* transitions;
    AFR_VEXU_INTERNAL_CALL(current_state_->get_transitions(transitions));
    for(const auto& it : *transitions){
        bool change_state;
        AFR_VEXU_INTERNAL_CALL(it.should_change_state(change_state));
        if(change_state){
            state* last_state = current_state_;
            std::string next_state;
            AFR_VEXU_INTERNAL_CALL(it.get_next_state(next_state));
            current_state_ = &state_map_.at(next_state);
            AFR_VEXU_INTERNAL_CALL(current_state_->on_state_entry(*last_state));
            break;
        }
    }
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::update_actions(){
    AFR_VEXU_INTERNAL_CALL(current_state_->update_actions());
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::get_state(std::string id, state*& result){
    result = &state_map_.at(id);
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::get_commandable(std::string id, commandable*& result){
    result = &commandable_map_.at(id);
    return SUCCESS;
}
