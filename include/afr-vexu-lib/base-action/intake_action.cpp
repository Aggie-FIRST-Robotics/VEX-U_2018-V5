namespace AFR::VexU::BaseAction{
    error_t intake_action::update_private(const double& delta_seconds){
        check_buttons();
        return commandable_.set_value(std::any{value_});
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"

    template<typename T>
    intake_action<T>::intake_action(const scheduled_update_t& update_period, commandable& commandable,
                                       const pros::controller_digital_e_t& input_1, const pros::controller_digital_e_t& input_2
                                       error_t* result = nullptr) : action(update_period, commandable, result),
                                                                    input_1_(input_1), input_2_(input_2){}

    error_t intake_action<T>::check_buttons(){
        bool val1 = false, val2 = false;
        BaseReadable::Controller::driver_controller->digital_is_pressed(input_1_, val1);
        BaseReadable::Controller::driver_controller->digital_is_pressed(input_2_, val2);

        if(val1 && !val2) value_ = 100;
        else if(val2 && !val1) value_ = -100;
        else value_ = 0;
        return SUCCESS
    }

    template<typename T>
    error_t intake_action<T>::set_inputs(const pros::controller_digital_e_t& input_1, const pros::controller_digital_e_t& input_2){
        check_buttons();
        return SUCCESS;
    }

#pragma clang diagnostic pop
}
