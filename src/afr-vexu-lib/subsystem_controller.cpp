#include <afr-vexu-lib/subsystem_controller.h>

AFR::VexU::subsystem_controller::subsystem_controller(
        const std::unordered_map<std::string, ordered_input&>& input_map,
        const std::unordered_map<std::string, AFR::VexU::state_controller&>& state_map) : input_map_(input_map),
                                                                                          state_map_(state_map),
                                                                                          ordered_inputs_(){
    std::vector<ordered_input*> order;
    for(auto& input_pair : input_map_){
        order.push_back(&input_map_.at(input_pair.first));
    }

    struct{
        bool operator()(const AFR::VexU::ordered_input* a, const AFR::VexU::ordered_input* b){
            return a->get_order() < b->get_order();
        }
    } sorter;
    std::sort(order.begin(), order.end(), sorter);

    for(auto item : order){
        ordered_inputs_.emplace_back(&item->get_input());
    }
}

AFR::VexU::result_t AFR::VexU::subsystem_controller::updateInputs(){
    for(auto it : ordered_inputs_){
        it->update();
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
        it.second.update_actions();
    }
    return SUCCESS;
};

const AFR::VexU::ordered_input& AFR::VexU::subsystem_controller::getInput(const std::string& id) const{
    return input_map_.at(id);
};

const AFR::VexU::state_controller& AFR::VexU::subsystem_controller::getStateMachine(const std::string& id) const{
    return state_map_.at(id);
};