#ifndef VEX_U_2018_V5_SET_VALUE_H
#define VEX_U_2018_V5_SET_VALUE_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    template<typename T>
    class set_value_action : public action{
        const T value_;
        error_t update_private(const double& delta_seconds) override;

    public:
        set_value_action(const scheduled_update_t& update_period, commandable& commandable, const T& value);
    };

    template<typename T>
    error_t set_value_action<T>::update_private(const double& delta_seconds){
        return commandable_.set_value(std::any{value_});
    }

    template<typename T>
    set_value_action<T>::set_value_action(const scheduled_update_t& update_period, commandable& commandable,
                                          const T& value) : action(update_period, commandable), value_(value){}
}

#endif //VEX_U_2018_V5_SET_VALUE_H
