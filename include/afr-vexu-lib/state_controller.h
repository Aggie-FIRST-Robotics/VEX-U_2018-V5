#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>
#include <any>

#include "state.h"
#include "defines.h"
#include "nameable.h"

namespace AFR::VexU{
    /**
     * Represents a state machine within a subsystem
     */
    class state_controller : public scheduled, public nameable{
        std::vector<state*> states_;
        std::vector<commandable*> commandables_;
        state* current_state_;

        /**
         * Calls update current state
         * @param delta_seconds from scheduled
         * @return error_t value if error encountered
         */
        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a state controller
         * @param update_period passed to scheduled
         * @param states contains all states by string
         * @param commandables the map of commandables by string
         * @param initial_state the initial state by string within state_map
         * @param result error_t value if error encountered
         */
        state_controller(
                const scheduled_update_t& update_period,
                const std::vector<state*>& states,
                const std::vector<commandable*>& commandables,
                state* initial_state,
                const std::string& name);

        /**
         * Updates current state, will stp if error encountered
         * @return error_t value if error encountered
         */
        void update_current_state()
        /**
         * Updates actions of current state
         * @return error_t value if error encountered
         */
        ;
        void update_actions();
        /**
         * Gets a state by string
         * @param name the string to search for
         * @param result the state found as a pointer
         * @return error_t value if error encountered
         */
        state* get_state(const std::string& name);
        std::vector<state*>& get_states();
        /**
         * Gets a commandable by string
         * @param name the string to search for
         * @param result the cmmandable found as a pointer
         * @return error_t value if error encountered
         */
        commandable* get_commandable(const std::string& name);
        std::vector<commandable*>& get_commandables();
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H