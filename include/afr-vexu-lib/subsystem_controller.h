#ifndef VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
#define VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include "ordered_input.h"
#include "state_controller.h"
#include "defines.h"

namespace AFR::VexU{
    /**
     * Represents an entire subsystem
     */
    class subsystem_controller{
    private:
        const std::unordered_map<std::string, ordered_input&> input_map_;
        std::vector<readable*> ordered_inputs_;
        const std::unordered_map<std::string, state_controller&> state_map_;

    public:
        /**
         * Creates a subsystem controller
         * @param input_map map of ordered inputs by string
         * @param state_map map of states by string
         * @param result error_t value if error encountered
         */
        subsystem_controller(const std::unordered_map<std::string, ordered_input&>& input_map,
                             const std::unordered_map<std::string, state_controller&>& state_map,
                             error_t* result = nullptr);

        /**
         * Updates readables in input_map_
         * @return error_t value if error encountered
         */
        error_t updateInputs();
        /**
         * Updates state transitions for the current state
         * @return error_t value if error encountered
         */
        error_t updateStates();
        /**
         * Updates current state's actions
         * @return error_t value if error encountered
         */
        error_t updateActions();
        /**
         * Gets ordered input by string
         * @param id string to search for
         * @param result ordered input result by pointer
         * @return error_t value if error encountered
         */
        error_t getInput(const std::string& id, ordered_input*& result) const;
        /**
         * Gets state by string
         * @param id string to search for
         * @param result state result by pointer
         * @return error_t value if error encountered
         */
        error_t getStateMachine(const std::string& id, state_controller*& result) const;
    };
}

#endif //VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
