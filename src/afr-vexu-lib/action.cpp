#include "afr-vexu-lib/action.h"

AFR::VexU::action::action(const scheduled_update_t& update_period_ms, AFR::VexU::commandable& commandable) : scheduled(
        update_period_ms), commandable_(commandable) {}
