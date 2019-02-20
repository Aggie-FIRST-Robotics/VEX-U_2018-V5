//
// Created by aamhi on 2/12/2019.
//

#include "afr-vexu-lib/action.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"

#ifndef VEX_U_2018_V5_JOYSTICK_H
#define VEX_U_2018_V5_JOYSTICK_H

#endif //VEX_U_2018_V5_JOYSTICK_H
namespace AFR::VexU::Robot::Shooter {

    class joystick : public action {

        BaseReadable::controller_analog_readable *stick;
        BaseReadable::controller_digital_readable *a_button_;
        BaseReadable::motor_encoder_velocity_readable *encoder_;

        void update_private(const double &delta_seconds) override;

    public:
        joystick(scheduled_update_t update_period, commandable *commandable,
                 BaseReadable::controller_analog_readable *stick_, const std::string &name,
                 BaseReadable::motor_encoder_velocity_readable *encoder);


    };


}