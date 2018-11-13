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
                             const std::unordered_map<std::string, state_controller&>& state_map,
                             error_t* result = nullptr);

        error_t updateInputs();
        error_t updateStates();
        error_t updateActions();
        error_t getInput(const std::string& id, ordered_input*& result) const;
        error_t getStateMachine(const std::string& id, state_controller*& result) const;
    };
}

#endif //VEX_U_2018_V5_SUBSYSTEM_CONTROLLER_H
