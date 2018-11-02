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
        const std::function<void(const state&)> on_state_entry_;

    public:
        state(const std::unordered_map<std::string, action&>& action_map,
              const std::vector<transition>& transitions, const std::function<void(const state&)>& on_state_entry);

        void update_actions();
        void on_state_entry(const state& previous);
        action& get_action(const std::string& identifier);
        const std::vector<transition>& get_transitions();
    };

    class transition{
    private:
        std::string next_state_;
        std::function<bool()> condition_function_;

    public:
        transition(const std::function<bool()>& condition_function, const std::string& next_state);

        bool should_change_state() const;
        std::string get_next_state() const;
    };
}

#endif //VEX_U_2018_V5_STATE_H
