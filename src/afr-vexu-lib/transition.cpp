

#include <afr-vexu-lib/transition.h>

AFR::VexU::transition::transition(std::function<bool()>& condition_function, const AFR::VexU::identifier_e& next_state)
        : condition_function_(condition_function), next_state_identifier_(
        next_state.get_identifier()){}

bool AFR::VexU::transition::should_change() const{
    return condition_function_();
}

std::string AFR::VexU::transition::get_next_state_identifier() const{
    return next_state_identifier_;
}
