#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>
#include <any>

#include "state.h"
#include "defines.h"

namespace AFR::VexU{
    /**
     * Represents a state machine within a subsystem
     */
    class state_controller : public scheduled{
        const std::unordered_map<std::string, state&> state_map_;
        const std::unordered_map<std::string, commandable&> commandable_map_;
        state* current_state_;

        /**
         * Calls update current state
         * @param delta_seconds from scheduled
         * @return error_t value if error encountered
         */
        error_t update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a state controller
         * @param update_period passed to scheduled
         * @param state_map contains all states by string
         * @param commandable_map the map of commandables by string
         * @param initial_state the initial state by string within state_map
         * @param result error_t value if error encountered
         */
        state_controller(const scheduled_update_t& update_period,
                         const std::unordered_map<std::string, state&>& state_map,
                         const std::unordered_map<std::string, commandable&>& commandable_map,
                         const std::string& initial_state, error_t* result = nullptr);

        /**
         * Updates current state, will stp if error encountered
         * @return error_t value if error encountered
         */
        error_t update_current_state()
        /**
         * Updates actions of current state
         * @return error_t value if error encountered
         */
        ;
        error_t update_actions();
        /**
         * Gets a state by string
         * @param id the string to search for
         * @param result the state found as a pointer
         * @return error_t value if error encountered
         */
        error_t get_state(std::string id, state*& result);
        /**
         * Gets a commandable by string
         * @param id the string to search for
         * @param result the cmmandable found as a pointer
         * @return error_t value if error encountered
         */
        error_t get_commandable(std::string id, commandable*& result);
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H