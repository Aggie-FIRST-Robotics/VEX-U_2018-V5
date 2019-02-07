#ifndef VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
#define VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include "readable.h"
#include "state_controller.h"
#include "defines.h"

namespace AFR::VexU{
    /**
     * Represents an entire subsystem
     */
    class subsystem_controller : public nameable{
    private:
        std::vector<readable*> inputs_;
        std::vector<state_controller*> state_controllers_;

    public:
        /**
         * Creates a subsystem controller
         * @param inputs map of ordered inputs by string
         * @param state_controllers map of states by string
         * @param result error_t value if error encountered
         */
        subsystem_controller(const std::vector<readable*>& inputs,
                             const std::vector<state_controller*>& state_controllers,
                             const std::string& name);

        /**
         * Updates readables in input_map_
         * @return error_t value if error encountered
         */
        void updateInputs();
        /**
         * Updates state transitions for the current state
         * @return error_t value if error encountered
         */
        void updateStates();
        /**
         * Updates current state's actions
         * @return error_t value if error encountered
         */
        void updateActions();
        /**
         * Gets ordered input by string
         * @param name string to search for
         * @param result ordered input result by pointer
         * @return error_t value if error encountered
         */
        readable* get_input(size_t name) const;
        std::vector<readable*>& get_inputs();
        /**
         * Gets state by string
         * @param name string to search for
         * @param result state result by pointer
         * @return error_t value if error encountered
         */
        state_controller* get_state_machine(const std::string& name) const;
        std::vector<state_controller*> get_state_machines();
    };
}

#endif //VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
