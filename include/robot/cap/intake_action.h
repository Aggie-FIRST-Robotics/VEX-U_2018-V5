//
// Created by aamhi on 2/6/2019.
//
#include "afr-vexu-lib/action.h"




#ifndef VEX_U_2018_V5_INTAKE_ACTION_H
#define VEX_U_2018_V5_INTAKE_ACTION_H

#endif //VEX_U_2018_V5_INTAKE_ACTION_H

namespace AFR::VexU::Robot::Cap{

    class intake_action : public action{
        error_t update_private(const double& delta_seconds) override;
        pros::controller_analog_e_t right_;
        pros::controller_analog_e_t left_;


    public:
        intake_action(const scheduled_update_t& update_period, commandable& commandable,
                      pros::controller_digital_e_t left, pros::controller_digital_e_t right)
        );




    };














}