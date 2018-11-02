#include "afr-vexu-lib/state_controller.h"

AFR::VexU::state_controller::state_controller(const std::unordered_map<std::string, AFR::VexU::state&>& state_map,
                                              const std::unordered_map<std::string, AFR::VexU::commandable&>& commandable_map,
                                              const std::string& initial_state) : state_map_(state_map),
                                                                                  commandable_map_(commandable_map),
                                                                                  current_state_(&state_map.at(
                                                                                          initial_state)){}

AFR::VexU::result_t AFR::VexU::state_controller::update_current_state(){
    for(const auto& it : current_state_->get_transitions()){
        if(it.should_change_state()){
            state* last_state = current_state_;
            current_state_ = &it.get_next_state();
            current_state_->on_state_entry(*last_state);
            break;
        }
    }
    return SUCCESS;
};

AFR::VexU::result_t AFR::VexU::state_controller::updateActions(){
    for(auto it : state_map_){
        it.second.update_actions();
    }
    return SUCCESS;
};

AFR::VexU::state& AFR::VexU::state_controller::getState(std::string id){
    return state_map_.at(id);
};

AFR::VexU::commandable& AFR::VexU::state_controller::getCommandable(std::string id){
    return commandable_map_.at(id);
};