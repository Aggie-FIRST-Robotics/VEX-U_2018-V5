#ifndef VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H
#define VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    /**
     * Action for equating a commandable to a value, represented by a pointer
     * @tparam T the type of value
     */
    template<typename T>
    class equivalent_value_action : public action{
        T* const value_ptr_;
        error_t update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a equivalent value action
         * @param update_period passed to scheduled
         * @param commandable passed to action
         * @param value_ptr the pointer to the value to be copied every update
         * @param result error_t value if error encountered
         */
        equivalent_value_action(const scheduled_update_t& update_period, commandable& commandable, const T* value_ptr,
                                error_t* result = nullptr);
    };

    template<typename T>
    error_t equivalent_value_action<T>::update_private(const double& delta_seconds){
        return commandable_.set_value(std::any{*value_ptr_});
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-non-const-parameter"
    template<typename T>
    equivalent_value_action<T>::equivalent_value_action(const scheduled_update_t& update_period,
                                                        commandable& commandable, const T* value_ptr, error_t* result)
            : action(update_period,
                     commandable, result),
              value_ptr_(value_ptr){}

#pragma clang diagnostic pop
}

#endif //VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H
