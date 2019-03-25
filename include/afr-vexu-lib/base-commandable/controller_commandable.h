#ifndef VEX_U_2018_V5_CONTROLLER_COMMANDABLE_H
#define VEX_U_2018_V5_CONTROLLER_COMMANDABLE_H

#include "main.h"
#include <string>
#include <string.h>

#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{

    class controller_commandable : public commandable<std::string>{

        pros::controller_id_e_t controller_;

        void set_value_private(std::string pattern, double delta_seconds) override;

    public:

        controller_commandable(const scheduled_update_t update_period, std::string pattern, pros::controller_id_e_t id, const std::string& name);
    };

}

#endif //VEX_U_2018_V5_MOTOR_COMMANDABLE_H
