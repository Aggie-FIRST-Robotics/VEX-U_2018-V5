#ifndef VEX_U_2018_V5_STATE_H
#define VEX_U_2018_V5_STATE_H

#include <string>
#include <vector>
#include <functional>

#include "afr-lib/nameable.h"

namespace AFR::VexU {
    class state;
    struct transition {
        std::function<bool()> transition_function;
        state* next_state;
        transition(std::function<bool()>& trans_func, state* state) : transition_function(trans_func), next_state(state) {}
    };
    /**
     * Represents a state within a state machine
     */
    class state : public nameable {
        std::vector<transition> transitions_;
        std::function<void(state*)> on_state_entry_;
        std::function<void(state*)> on_state_exit_;

    public:
        /**
         * Creates a state
         * @param transitions the vector of transitions to be checked in order
         * @param on_state_entry the function that is called when this state is entered
         * @param on_state_exit the function that is called when this state is exited
         * @param result error_t value if error encountered
         */
        explicit state(const std::string& name);

        /**
         * Executes on state entry function
         * @return error_t value if error encountered
         */
        void on_state_entry(state* prev_state);
        /**
         * Executes on state exit function
         * @return error_t value if error encountered
         */
        void on_state_exit(state* next_state);

        /**
         * Sets on state entry function
         * @param on_state_entry the function to set the on state entry function
         * @return error_t value if error encountered
         */
        void set_on_state_entry(const std::function<void(state*)>& on_state_entry);
        /**
         * Sets on state exit function
         * @param on_state_exit the function to set the on state exit function
         * @return error_t value if error encountered
         */
        void set_on_state_exit(const std::function<void(state*)>& on_state_exit);
        /**
         * Returns transitions vector
         * @return error_t value if error encountered
         */
        std::vector<transition>& get_transitions();
        /**
         * Adds transition to the transition vector
         * @param transition_function the function check of the new transition
         * @param next_state the next state of the transition
         * @return error_t value if error encountered
         */
        void add_transition(std::function<bool()> transition_function, state* next_state);
        /**
         * Sets the transition vector to a new transition vector
         * @param transitions the vector of transitions to be checked in order
         * @return error_t value if error encountered
         */
        void set_transitions(const std::vector<transition>& transitions);
        /**
         * Clears the transition vector
         * @return error_t value if error encountered
         */
        void clear_transitions();
        /**
         * Returns the next state
         * @return error_t value if error encountered
         */
        state* get_next_state() const;
    };
}

#endif //VEX_U_2018_V5_STATE_H
