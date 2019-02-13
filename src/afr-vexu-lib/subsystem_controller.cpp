#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU{
    subsystem_controller::subsystem_controller(
            const std::vector<readable*>& inputs,
            const std::vector<state_controller*>& state_controllers,
            const std::string& name)
            : nameable(name), inputs_(inputs), state_controllers_(state_controllers){}

    void subsystem_controller::updateInputs(){
        for(auto& input : inputs_){
            input->update();
        }
    };

    void subsystem_controller::updateStates(){
        for(auto* state_controller : state_controllers_){
            state_controller->update_current_state();
        }
    };

    void subsystem_controller::updateActions(){
        for(auto state_controller : state_controllers_){
            state_controller->update_actions();
        }
    };

    readable* subsystem_controller::get_input(const std::string& name) const{
        for(auto ordered_input : inputs_){
            if(ordered_input->get_name() == name){
                return ordered_input;
            }
        }
        return nullptr;
    };

    state_controller* subsystem_controller::get_state_machine(const std::string& name) const{
        for(auto state_controller : state_controllers_){
            if(state_controller->get_name() == name){
                return state_controller;
            }
        }
        return nullptr;
    }

    std::vector<readable*>& subsystem_controller::get_inputs(){
        return inputs_;
    }

    std::vector<state_controller*> subsystem_controller::get_state_machines(){
        return state_controllers_;
    };
}