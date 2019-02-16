//
// Created by aamhi on 2/12/2019.
//

#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "robot/shooter/joystick.h"

namespace AFR::VexU::Robot::Shooter {
    joystick::joystick(scheduled_update_t update_period, commandable *commandable,
                       BaseReadable::controller_analog_readable *stick_, const std::string &name,
                       BaseReadable::motor_encoder_readable *encoder) : action(update_period, commandable, name),
                                                                        stick(stick_), encoder_{encoder} {
        a_button_ = BaseReadable::get_controller_digital_readable(pros::E_CONTROLLER_MASTER,
                                                                  pros::E_CONTROLLER_DIGITAL_A);
    }


    void joystick::update_private(const double &delta_seconds) {
        //  for(;;)std::cout << "4";

//      for(;;) {
        auto val = stick->get_position();
        pros::lcd::set_text(2, "Controller: " + std::to_string(val));
        pros::lcd::set_text(1, "Encoder: " + std::to_string(encoder_->get_position()));
        if (a_button_->is_pressed()) {
            encoder_->tare_position();
        }

//          std::cout << get_name() << " value: " << val;
        commandable_->set_value(static_cast<int16_t>(val * 12000 / 127));

//      }
        //
        // .std::cout << get_name() << " value: " << std::any_cast<int16_t>(commandable_->get_current_value());
    }


}