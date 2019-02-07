namespace AFR::VexU::BaseAction{
    template<typename T>
    void equivalent_value_action<T>::update_private(const double& delta_seconds){
        return commandable_.set_value(std::any{*value_ptr_});
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"

    template<typename T>
    equivalent_value_action<T>::equivalent_value_action(const scheduled_update_t& update_period,
                                                        commandable& commandable, const T* value_ptr, error_t* result)
            : action(update_period,
                     commandable, <#initializer#>),
              value_ptr_(value_ptr){}

#pragma clang diagnostic pop
}
