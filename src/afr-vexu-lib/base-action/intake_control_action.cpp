#include "afr-vexu-lib/base-action/intake_control_action.h"

namespace AFR::VexU::BaseAction {
    intake_control_action::intake_control_action(const AFR::VexU::scheduled_update_t& update_period,
                                                 AFR::VexU::commandable* commandable,
                                                 AFR::VexU::BaseReadable::controller_digital_readable* outtake_button,
                                                 AFR::VexU::BaseReadable::controller_digital_readable* intake_button,
                                                 int16_t outtake_val,
                                                 int16_t intake_val, int16_t hold_val, const std::string& name) :
            action(update_period, commandable, name), outtake_button_(outtake_button), intake_button_(intake_button),
            outtake_val_(outtake_val), intake_val_(intake_val), hold_val_(hold_val){}

    void intake_control_action::update_private(const double &delta_seconds) {
        if(outtake_button_ != nullptr && outtake_button_->is_pressed()){
            commandable_->set_value(outtake_val_);

        }
        else if(intake_button_ != nullptr && intake_button_->is_pressed()){
            commandable_->set_value(intake_val_);
        }
        else{
            commandable_->set_value(hold_val_);
        }
    }
}