#ifndef VEX_U_2018_V5_STATE_H
#define VEX_U_2018_V5_STATE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "scheduled.h"
#include "action.h"
#include "transition.h"

namespace AFR::VexU{
    typedef std::unordered_map<std::string, action_no_temp&> action_map;
    typedef std::vector<transition> transition_vector;

    class state : public scheduled{
        action_map* actions_;
        transition_vector* transitions_;
        std::function<void()> on_state_entry_;

    public:
        explicit state(const unsigned int& update_period_ms, action_map* actions, transition_vector* transitions,
                       std::function<void()>& on_state_entry);

        void update_actions();
        void on_state_entry();

        action_no_temp& get_action(const identifier_e& identifier);
        transition_vector* get_transitions();
    };
}

#endif //VEX_U_2018_V5_STATE_H
