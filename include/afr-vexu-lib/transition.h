#ifndef VEX_U_2018_V5_TRANSITION_H
#define VEX_U_2018_V5_TRANSITION_H

#include <functional>

#include "identifier_e.h"

namespace AFR::VexU{
    class transition{
        std::function<bool()> condition_function_;
        std::string next_state_identifier_;

    public:
        transition(std::function<bool()>& condition_function, const identifier_e& next_state);
        bool should_change() const;
        std::string get_next_state_identifier() const;
    };
}

#endif //VEX_U_2018_V5_TRANSITION_H
