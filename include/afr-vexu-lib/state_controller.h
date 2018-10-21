#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>

#include "state.h"

namespace AFR::VexU{
    typedef std::unordered_map<std::string, state> state_map_t;
    typedef std::unordered_map<std::string, commandable_no_temp&> commandable_map_t;

    class state_controller{
        state_map_t& state_map_;
        commandable_map_t& commandable_map_;
        state& current_state;

    public:
        state_controller(state_map_t& state_map, commandable_map_t& commandable_map,
                         const identifier_e& initial_identifier);

        void update_current_state();
        void update_actions();
        state& get_state(const identifier_e& identifier);
        commandable_no_temp& get_commandable(const identifier_e& identifier);
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H
