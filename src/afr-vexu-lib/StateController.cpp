#include "StateController.h"

StateController::StateController(std::unordered_map<std::string, State> &states, std::unordered_map<std::string, Commandable> &commandables) {
    state_map = states;
    commandable_map = commandables;
};

result_t StateController::updateCurrentState() {
    for(auto it : current_state.getTransitions()) {
        if(it->changeState()) {
            current_state = it->getNextState();
            current_state.onStateEntry();
            break;
        }
    }
    return SUCCESS;
};

result_t StateController::updateActions() {
    for(auto it : state_map) {
        it->updateActions();
    }
    return SUCCESS;
};

State& StateController::getState(std::string id) {
    return state_map[id];
};

Commandable& StateController::getCommandable(std::string id) {
    return commandable_map[id]
};