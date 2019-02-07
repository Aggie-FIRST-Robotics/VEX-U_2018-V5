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
                                                                                                           std::make_pair(
                                                                                                                   initial_state,
                                                                                                                   &state_map.at(
                                                                                                                           initial_state))){
    if(result != nullptr && *result == SUCCESS){
        *result = current_state_.second->on_state_entry(initial_state);
    }
    else if(result == nullptr){
        current_state_.second->on_state_entry(initial_state);
    }
}

AFR::VexU::error_t AFR::VexU::state_controller::update_current_state(){
    try{
        const std::vector<transition>* transitions;
        try{
            AFR_VEXU_INTERNAL_CALL(current_state_.second->get_transitions(transitions));
        }
        catch(std::bad_any_cast& e){
            std::cerr << "Error Here! 4" << std::endl;
            throw e;
        }
        for(const auto& it : *transitions){
            bool change_state;
            try{
                AFR_VEXU_INTERNAL_CALL(it.should_change_state(change_state));
            }
            catch(std::bad_any_cast& e){
                std::cerr << "Error Here! 3" << std::endl;
                throw e;
            }
            if(change_state){
                std::string last_state = current_state_.first;
                std::string next_state;
                AFR_VEXU_INTERNAL_CALL(it.get_next_state(next_state));
                current_state_.second->on_state_exit(next_state);
                AFR_TRY(current_state_.second = &state_map_.at(next_state), next_state);
                current_state_.first = next_state;
                AFR_VEXU_INTERNAL_CALL(current_state_.second->on_state_entry(last_state));
                break;
            }
        }
    }
    catch(std::bad_any_cast& e){
        std::cerr << "Error Here! 2" << std::endl;
        throw e;
    }
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::update_actions(){
    AFR_VEXU_INTERNAL_CALL(current_state_.second->update_actions());
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::get_state(std::string id, state*& result){
    AFR_TRY(result = &state_map_.at(id), id);
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::state_controller::get_commandable(std::string id, commandable*& result){
    AFR_TRY(result = &commandable_map_.at(id), id);
    return SUCCESS;
}
