#include "robot/drive/arcade_drive_action.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::Robot::Drive{
    arcade_drive_action::arcade_drive_action(scheduled_update_t update_period, commandable* commandable,
                                             BaseReadable::controller_analog_readable* left_stick,
                                             BaseReadable::controller_analog_readable* right_stick, bool is_right,
                                             const std::string& name)
            : action(update_period, commandable, name), is_right(is_right), left_stick_(left_stick),
              right_stick_(right_stick){}

    void arcade_drive_action::update_private(const double& delta_seconds){
        auto right_val = right_stick_->get_position();
        auto left_val = left_stick_->get_position();
        if(is_right){
            commandable_->set_value(int16_t((left_val - right_val) * 12000 / 128));
        }
        else{
            commandable_->set_value(int16_t((left_val + right_val) * 12000 / 128));
        }
        std::cout << get_name() << " value: " << std::any_cast<int16_t>(commandable_->get_current_value());
    }
}
