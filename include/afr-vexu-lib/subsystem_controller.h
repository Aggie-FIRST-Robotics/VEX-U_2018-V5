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
    class subsystem_controller{
    private:
        const std::unordered_map<std::string, ordered_input&> input_map_;
        std::vector<readable*> ordered_inputs_;
        const std::unordered_map<std::string, state_controller&>& state_map_;

    public:
        subsystem_controller(const std::unordered_map<std::string, ordered_input&>& input_map,
                             const std::unordered_map<std::string, state_controller&>& state_map);

        error_t updateInputs();
        error_t updateStates();
        error_t updateActions();
        const ordered_input& getInput(const std::string& id) const;
        const state_controller& getStateMachine(const std::string& id) const;
    };
}

#endif //VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
