#include "SubsystemController.h"

StateController::StateController(std::unordered_map<std::string, OrderedInput> inputs, std::unordered_map<std::string, StateController> statemachines) {
    input_map = inputs;
    state_map = statemachines;
    ordered_inputs = std::vector<Readable>(input_map.size());
    for(auto it = input_map.begin(); it != input_map.end(); it++) {
        
    }
};

result_t StateController::updateInputs() {
    
    for(auto it : ordered_inputs) {
        it->update();
    }
    return SUCCESS;
};

result_t StateController::updateStates(){
    for(auto it : state_map) {
        it->updateCurrentState();
    }
    return SUCCESS;
};

result_t StateController::updateActions(){
    for(auto it : state_map) {
        it->updateActions();
    }
    return SUCCESS;
};

OrderedInput& StateController::getInput(std::string id) {
    return input_map[id];
};

OrderedInput& StateController::getStateMachine(std::string id) {
    return state_map[id];
};