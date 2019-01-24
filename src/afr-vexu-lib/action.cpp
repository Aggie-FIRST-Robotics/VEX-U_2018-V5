#include "afr-vexu-lib/action.h"

namespace AFR::VexU{
    AFR::VexU::action::action(const scheduled_update_t& update_period, AFR::VexU::commandable& commandable,
                              error_t* result)
            : scheduled(
            update_period, result), commandable_(commandable){}

    error_t AFR::VexU::action::on_state_entry(const std::string& previous_state){
        return SUCCESS;
    }

    error_t action::on_state_exit(const std::string& next_state){
        return SUCCESS;
    }
}