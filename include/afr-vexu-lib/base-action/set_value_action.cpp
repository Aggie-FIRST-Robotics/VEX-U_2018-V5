namespace AFR::VexU::BaseAction{
    template<typename T>
    error_t set_value_action<T>::update_private(const double& delta_seconds){
        return commandable_.set_value(std::any{value_});
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"

    template<typename T>
    set_value_action<T>::set_value_action(const scheduled_update_t& update_period, commandable& commandable,
                                          const T& value, error_t* result) : action(update_period, commandable, result),
                                                                             value_(value){}

    template<typename T>
    error_t set_value_action<T>::set_value(const T& value){
        value_ = value;
        return SUCCESS;
    }

#pragma clang diagnostic pop
}
