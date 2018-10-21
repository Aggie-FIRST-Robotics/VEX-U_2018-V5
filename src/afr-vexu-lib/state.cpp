#include <afr-vexu-lib/state.h>

AFR::VexU::state::state(const unsigned int& update_period_ms, AFR::VexU::action_map* actions,
                        AFR::VexU::transition_vector* transitions, std::function<void()>& on_state_entry) : scheduled(
        update_period_ms), actions_(actions), transitions_(transitions), on_state_entry_(on_state_entry){}

void AFR::VexU::state::update_actions(){
    for(auto& action : *actions_){
        action.second.update();
    }
}

void AFR::VexU::state::on_state_entry(){
    on_state_entry_();
}

AFR::VexU::action_no_temp& AFR::VexU::state::get_action(const AFR::VexU::identifier_e& identifier){
    return actions_->at(identifier.get_identifier());
}

AFR::VexU::transition_vector* AFR::VexU::state::get_transitions(){
    return transitions_;
}
