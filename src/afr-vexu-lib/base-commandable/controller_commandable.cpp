#include "afr-vexu-lib/base-commandable/controller_commandable.h"

namespace AFR::VexU::BaseCommandable{

    void controller_commandable::set_value_private(std::string pattern, double delta_seconds){
        pros::c::controller_rumble(controller_,pattern.substr(0,8).c_str());
    }

    controller_commandable::controller_commandable(const scheduled_update_t update_period, std::string pattern, pros::controller_id_e_t id, const std::string& name)
            : commandable<std::string>(update_period, name), nameable(name), controller_(id){
    }
}
