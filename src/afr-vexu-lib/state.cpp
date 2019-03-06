#include "afr-vexu-lib/state.h"

namespace AFR::VexU{
    state::state(const std::vector<transition>& transitions,
                    const std::function<void(state*)>& on_state_entry,
                    const std::function<void(state*)>& on_state_exit,
                    const std::string& name)
            : nameable(name), transitions_(transitions), on_state_entry_(on_state_entry), on_state_exit_(on_state_exit) {}

    void state::on_state_entry() {
        on_state_entry_();
    }

    void state::on_state_exit() {
        on_state_exit_();
    }

    void state::set_on_state_entry(const std::function<void>& on_state_entry) {
        on_state_entry_ = on_state_entry;
    }

    void state::set_on_state_exit(const std::function<void>& on_state_exit) {
        n_state_exit_ = on_state_exit;
    }

    std::vector<std::pair <std::function<bool()>, state*>>& state::get_transitions(){
        return transitions_;
    }

    void state::add_transition(std::function<bool()> transition_function, state* next_state) {
        transitions_.emplace_back(transition_function,next_state);
    }

    void state::set_transitions(const std::vector<std::pair <std::function<bool()>, state*>>& transitions) {
        transitions_ = transitions;
    }

    void clear_transitions() {
        transitions_.clear();
    }

    state* state::get_next_state() const{
        for(auto transition : transitions_) {
            if(transition.first)
                return transition.second;
        }
        return this;
    }
}
