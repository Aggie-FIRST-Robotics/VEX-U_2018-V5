namespace AFR::VexU::BaseAction {
    intake_control_action::intake_control_action(const AFR::VexU::scheduled_update_t &update_period,
                                 AFR::VexU::commandable *commandable,
                                 AFR::VexU::BaseReadable::controller_digital_readable *left,
                                 AFR::VexU::BaseReadable::controller_digital_readable *right, const std::string &name) :
            action(update_period, commandable, name), left_(left), right_(right) {


    }


    void intake_control_action::update_private(const double &delta_seconds) {
        bool leftval = left_->is_pressed();
        bool rightval = right_->is_pressed();


        if (leftval) {
            commandable_->set_value(-6000);

        } else if (rightval) {
            commandable_->set_value(6000);
        } else {
            commandable_->set_value(0);
        }


    }


}