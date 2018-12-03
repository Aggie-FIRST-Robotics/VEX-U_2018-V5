#ifndef VEX_U_2018_V5_SET_VALUE_H
#define VEX_U_2018_V5_SET_VALUE_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    /**
     * An action that sets a commandable to a single value
     * @tparam T the type of constant value
     */
    template<typename T>
    class set_value_action : public action{
        T value_;
        error_t update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a set value action
         * @param update_period passed to scheduled
         * @param commandable the commandable to set
         * @param value the constant value to be set
         * @param result error_t value if error encountered
         */
        set_value_action(const scheduled_update_t& update_period, commandable& commandable, const T& value,
                         error_t* result = nullptr);

        error_t set_value(const T& value);
    };

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

#endif //VEX_U_2018_V5_SET_VALUE_H
