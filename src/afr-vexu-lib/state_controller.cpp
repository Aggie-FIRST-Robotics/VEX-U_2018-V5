
#include <afr-vexu-lib/state_controller.h>

void AFR::VexU::state_controller::update_private(const double& delta_seconds){
    update_current_state();
};

AFR::VexU::state_controller::state_controller(const scheduled_update_t& update_period,
                                              const std::unordered_map<std::string, AFR::VexU::state&>& state_map,
                                              const std::unordered_map<std::string, AFR::VexU::commandable&>& commandable_map,
                                              const std::string& initial_state) : scheduled(update_period),
                                                                                  state_map_(state_map),
                                                                                  commandable_map_(commandable_map),
                                                                                  current_state_(&state_map.at(
                                                                                          initial_state)){
    current_state_->on_state_entry(*current_state_);
}

AFR::VexU::result_t AFR::VexU::state_controller::update_current_state(){
    for(const auto& it : current_state_->get_transitions()){
        if(it.should_change_state()){
            state* last_state = current_state_;
            current_state_ = &state_map_.at(it.get_next_state());
            current_state_->on_state_entry(*last_state);
            break;
        }
    }
    return SUCCESS;
};

AFR::VexU::result_t AFR::VexU::state_controller::update_actions(){
    current_state_->update_actions();
    return SUCCESS;
};

AFR::VexU::state& AFR::VexU::state_controller::get_current_state(std::string id){
    return state_map_.at(id);
};

AFR::VexU::commandable& AFR::VexU::state_controller::get_commandable(std::string id){
    return commandable_map_.at(id);
}
