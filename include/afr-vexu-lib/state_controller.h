#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>
#include <any>

#include "state.h"
#include "defines.h"

namespace AFR::VexU{
    class state_controller{
        const std::unordered_map<std::string, state&> state_map_;
        const std::unordered_map<std::string, commandable&> commandable_map_;
        state* current_state_;

    public:
        state_controller(const std::unordered_map<std::string, state&>& state_map,
                         const std::unordered_map<std::string, commandable&>& commandable_map,
                         const std::string& initial_state);

        result_t update_current_state();
        result_t update_actions();
        state& get_current_state(std::string id);
        commandable& get_commandable(std::string id);
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H