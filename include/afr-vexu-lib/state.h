#ifndef VEX_U_2018_V5_STATE_H
#define VEX_U_2018_V5_STATE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>

#include "scheduled.h"
#include "action.h"

namespace AFR::VexU{
    class transition;

    class state{
        const std::unordered_map<std::string, action&> action_map_;
        const std::vector<transition> transitions_;
        const std::function<error_t(const state&)> on_state_entry_;

    public:
        state(const std::unordered_map<std::string, action&>& action_map,
              const std::vector<transition>& transitions, const std::function<error_t(const state&)>& on_state_entry,
              error_t* result = nullptr);

        error_t update_actions();
        error_t on_state_entry(const state& previous);
        error_t get_action(const std::string& identifier, action*& result);
        error_t get_transitions(const std::vector<transition>*& result);
    };

    class transition{
    private:
        std::string next_state_;
        std::function<error_t(bool&)> condition_function_;

    public:
        transition(const std::function<error_t(bool&)>& condition_function, const std::string& next_state,
                   error_t* result = nullptr);

        error_t should_change_state(bool& result) const;
        error_t get_next_state(std::string& result) const;
    };
}

#endif //VEX_U_2018_V5_STATE_H
