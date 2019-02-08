//
// Created by aamhi on 2/6/2019.
//
#include "afr-vexu-lib/action.h"




#ifndef VEX_U_2018_V5_INTAKE_ACTION_H
#define VEX_U_2018_V5_INTAKE_ACTION_H

//VEX_U_2018_V5_INTAKE_ACTION_H

namespace AFR::VexU::Robot::Cap{

    class intake_action : public action{

        pros::controller_digital_e_t right_;
        pros::controller_digital_e_t left_;
        void update_private(const double& delta_seconds) override;

    public:
        intake_action(const scheduled_update_t& update_period, commandable& commandable,
                      pros::controller_digital_e_t left, pros::controller_digital_e_t right);





    };


}
#endif
