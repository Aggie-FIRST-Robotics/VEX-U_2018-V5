#include "afr-vexu-lib/base-action/intake_control_action.h"

namespace AFR::VexU::BaseAction {
    intake_control_action::intake_control_action(const AFR::VexU::scheduled_update_t &update_period,
                                                 AFR::VexU::commandable *commandable,
                                                 AFR::VexU::BaseReadable::controller_digital_readable* outtake_button,
                                                 AFR::VexU::BaseReadable::controller_digital_readable* intake_button,
                                                 const std::string& name) :
            action(update_period, commandable, name), outtake_button_(outtake_button), intake_button_(intake_button){


    }

    void intake_control_action::update_private(const double &delta_seconds) {
        if(outtake_button_->is_pressed()){
            commandable_->set_value(static_cast<int16_t>(-12000));

        }
        else if(intake_button_->is_pressed()){
            commandable_->set_value(static_cast<int16_t>(12000));
        }
        else{
            commandable_->set_value(static_cast<int16_t>(3000));
        }
    }
}