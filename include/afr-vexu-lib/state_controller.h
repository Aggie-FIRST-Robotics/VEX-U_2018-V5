#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>
#include <any>

#include "state.h"
#include "defines.h"

namespace AFR::VexU{
    class state_controller : public scheduled{
        const std::unordered_map<std::string, state&> state_map_;
        const std::unordered_map<std::string, commandable&> commandable_map_;
        state* current_state_;

        void update_private(const double& delta_seconds) override;

    public:
        state_controller(const scheduled_update_t& update_period,
                         const std::unordered_map<std::string, state&>& state_map,
                         const std::unordered_map<std::string, commandable&>& commandable_map,
                         const std::string& initial_state);

        error_t update_current_state();
        error_t update_actions();
        state& get_current_state(std::string id);
        commandable& get_commandable(std::string id);
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H