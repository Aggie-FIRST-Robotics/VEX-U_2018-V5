namespace AFR::VexU::BaseAction{
    template<typename T>
    void equivalent_value_action<T>::update_private(const double& delta_seconds){
        return commandable_->set_value(*value_ptr_);
    }

    template<typename T>
    equivalent_value_action<T>::equivalent_value_action(scheduled_update_t update_period, commandable* commandable,
                                                        const T* value_ptr, const std::string& name)
            : action(update_period, commandable, name), value_ptr_(value_ptr){}
}
