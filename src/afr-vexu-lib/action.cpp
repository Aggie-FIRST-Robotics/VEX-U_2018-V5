#include "afr-vexu-lib/action.h"

namespace AFR::VexU{
    action::action(scheduled_update_t update_period, commandable& commandable, const std::string& name)
            : scheduled(update_period), nameable(name), commandable_(commandable){}

    void action::on_state_entry(state* previous_state){}

    void action::on_state_exit(state* next_state){}
}