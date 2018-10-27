#include "afr-vexu-lib/action.h"

AFR::VexU::action::action(const unsigned int &update_period_ms, AFR::VexU::commandable *commandable) : scheduled(
        update_period_ms), commandable_(commandable) {}
