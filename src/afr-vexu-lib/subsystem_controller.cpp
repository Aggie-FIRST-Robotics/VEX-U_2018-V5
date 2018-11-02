#include <afr-vexu-lib/subsystem_controller.h>

AFR::VexU::subsystem_controller::subsystem_controller(
        const std::unordered_map<std::string, ordered_input>& input_map,
        const std::unordered_map<std::string, AFR::VexU::state_controller&>& state_map) : input_map_(input_map),
                                                                                          state_map_(state_map),
                                                                                          ordered_inputs_(){
    std::vector<std::pair<std::string, ordered_input>&> order;
    for(const auto& input_pair : input_map_){
        for(size_t x = 0; x <= order.size(); x++){
            if(x == order.size()){
                order.emplace_back(input_pair);
                break;
            }
            if(order[x].second.get_order() < input_pair.second.get_order()){
                order.emplace(order.begin() + x + 1, input_pair);
            }
        }
    }
    for(auto item : order){
        ordered_inputs_.emplace_back(item.second.get_input());
    }
}

AFR::VexU::result_t AFR::VexU::subsystem_controller::updateInputs(){
    for(auto it : ordered_inputs_){
        it.update();
    }
    return SUCCESS;
};

AFR::VexU::result_t AFR::VexU::subsystem_controller::updateStates(){
    for(auto it : state_map_){
        it.second.update_current_state();
    }
    return SUCCESS;
};

AFR::VexU::result_t AFR::VexU::subsystem_controller::updateActions(){
    for(auto it : state_map_){
        it.second.update_current_state();
    }
    return SUCCESS;
};

const AFR::VexU::ordered_input& AFR::VexU::subsystem_controller::getInput(const std::string& id) const{
    return input_map_.at(id);
};

const AFR::VexU::state_controller& AFR::VexU::subsystem_controller::getStateMachine(const std::string& id) const{
    return state_map_.at(id);
};