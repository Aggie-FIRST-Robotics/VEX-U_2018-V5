#ifndef VEX_U_2018_V5_STATE_H
#define VEX_U_2018_V5_STATE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>

#include "scheduled.h"
#include "action.h"

namespace AFR::VexU{
    class state;

    /**
     * Represents a true or false function tied to a state
     */
    class transition : public nameable{
    private:
        state*& next_state_;
        std::function<bool()> condition_function_;

    public:
        /**
         * Creates a transition
         * @param condition_function the function that can return an error, and will cause a transition if parameter is assigned true
         * @param next_state the state to transition to if the function is true
         * @param result error_t value if error encountered
         */
        transition(const std::function<bool()>& condition_function, state*& next_state, const std::string& name);

        /**
         * Checks the functon assigned in the constructor and tells whether or not to change state
         * @param result true if state should change, false if otherwise
         * @return error_t value if error encountered
         */
        bool should_change_state() const;
        /**
         * Returns the state this transition says to change to
         * @param result the state in the form of a string, can be found in the unordered map
         * @return error_t value if error encountered
         */
        state* get_next_state() const;
    };

    /**
     * Represents a state within a state machine
     */
    class state : public nameable{
        std::vector<action*> actions_;
        std::vector<transition> transitions_;
        std::function<void(state*)> on_state_entry_;

    public:
        /**
         * Creates a state
         * @param action_map the map of strings to actions this state contains, should be the same size as the commandables of the state_controller
         * @param transitions the vector of transitions to be checked in order
         * @param on_state_entry the function that is called when this state is entered
         * @param result error_t value if error encountered
         */
        state(const std::vector<action*>& action_map, const std::vector<transition>& transitions,
              const std::function<void(state*)>& on_state_entry, const std::string& name);

        /**
         * Updates all actions in map, will stop if action returns error
         * @return error_t value if error encountered
         */
        void update_actions();
        /**
         * Executes on state entry function
         * @param previous the previous state
         * @return error_t value if error encountered
         */
        void on_state_entry(state* previous);
        void on_state_exit(state* next);
        /**
         * Used to get an action by string
         * @param name the string to search for
         * @param result the action requested
         * @return error_t value if error encountered
         */
        action* get_action(const std::string& name);
        std::vector<action*>& get_actions();
        /**
         * Used to get the transition vector for this state
         * @param result
         * @return error_t value if error encountered
         */
        std::vector<transition>& get_transitions();
    };
}

#endif //VEX_U_2018_V5_STATE_H
