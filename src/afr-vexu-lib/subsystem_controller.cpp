#include "afr-vexu-lib/subsystem_controller.h"

AFR::VexU::subsystem_controller::subsystem_controller(
        const std::unordered_map<std::string, ordered_input&>& input_map,
        const std::unordered_map<std::string, AFR::VexU::state_controller&>& state_map,
        error_t* result) : input_map_(
        input_map),
                                                                                                           state_map_(state_map),
                                                                                                           ordered_inputs_(){
    if(result != nullptr){
        *result = SUCCESS;
    }
    std::vector<ordered_input*> order;
    for(auto& input_pair : input_map_){
        order.push_back(&input_map_.at(input_pair.first));
    }

    struct{
        bool operator()(const AFR::VexU::ordered_input* a, const AFR::VexU::ordered_input* b){
            order_t result_a, result_b;
            if(a->get_order(result_a) != SUCCESS) throw std::runtime_error{""};
            if(b->get_order(result_b) != SUCCESS) throw std::runtime_error{""};
            return result_a < result_b;
        }
    } sorter;
    try{
        std::sort(order.begin(), order.end(), sorter);
    }
    catch(...){
        if(result != nullptr){
            *result = GENERIC_FAILURE;
        }
        return;
    }

    if(result != nullptr){
        for(auto item : order){
            readable* res;
            *result = item->get_input(res);
            if(*result != SUCCESS) break;
            ordered_inputs_.emplace_back(res);
        }
    }
    else{
        for(auto item : order){
            readable* res;
            item->get_input(res);
            ordered_inputs_.emplace_back(res);
        }
    }
}

AFR::VexU::error_t AFR::VexU::subsystem_controller::updateInputs(){
    for(auto it : ordered_inputs_){
        AFR_VEXU_INTERNAL_CALL(it->update());
    }
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::subsystem_controller::updateStates(){
    for(auto it : state_map_){
        AFR_VEXU_INTERNAL_CALL(it.second.update_current_state());
    }
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::subsystem_controller::updateActions(){
    for(auto it : state_map_){
        AFR_VEXU_INTERNAL_CALL(it.second.update_actions());
    }
    return SUCCESS;
};

AFR::VexU::error_t AFR::VexU::subsystem_controller::getInput(const std::string& id, ordered_input*& result) const{
    result = &input_map_.at(id);
    return SUCCESS;
};

AFR::VexU::error_t
AFR::VexU::subsystem_controller::getStateMachine(const std::string& id, state_controller*& result) const{
    result = &state_map_.at(id);
    return SUCCESS;
};