namespace AFR::VexU::BaseAction{
    template<typename T>
    void set_value_action<T>::update_private(const double& delta_seconds){
//        std::cout << "Called after " << delta_seconds * 1000 << " milli-seconds. Should be " << update_period_ << std::endl;
        commandable_->set_value(value_);
    }

    template<typename T>
    set_value_action<T>::set_value_action(scheduled_update_t update_period, commandable* commandable, T value,
                                          const std::string& name)
            : action(update_period, commandable, name), value_(value){}

    template<typename T>
    void set_value_action<T>::set_value(T value){
        value_ = value;
    }
}
