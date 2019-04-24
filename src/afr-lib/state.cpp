#include "afr-lib/state.h"

namespace AFR::VexU{
    state::state(const std::string& name)
            : nameable(name), transitions_(), on_state_entry_(), on_state_exit_(){}

    void state::on_state_entry(state* prev_state) {
        if(on_state_exit_ == nullptr){
            throw std::runtime_error{"No on state entry for " + get_name()};
        }
        on_state_entry_(prev_state);
    }

    void state::on_state_exit(state* next_state) {
        if(on_state_exit_ == nullptr){
            throw std::runtime_error{"No on state exit for " + get_name()};
        }
        on_state_exit_(next_state);
    }

    void state::set_on_state_entry(const std::function<void(state*)>& on_state_entry){
        on_state_entry_ = on_state_entry;
    }

    void state::set_on_state_exit(const std::function<void(state*)>& on_state_exit){
        on_state_exit_ = on_state_exit;
    }

    std::vector<transition>& state::get_transitions(){
        return transitions_;
    }

    void state::add_transition(std::function<bool()> transition_function, state* next_state) {
        transitions_.emplace_back(transition_function,next_state);
    }

    void state::set_transitions(const std::vector<transition>& transitions) {
        transitions_ = transitions;
    }

    void state::clear_transitions(){
        transitions_.clear();
    }

    state* state::get_next_state() const{
        for(const auto& transition : transitions_){
            if(transition.transition_function()){
                return transition.next_state;
            }
        }
        return nullptr;
    }
}
