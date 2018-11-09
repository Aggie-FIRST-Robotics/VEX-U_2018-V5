#ifndef VEX_U_2018_V5_SET_VALUE_H
#define VEX_U_2018_V5_SET_VALUE_H

#include "../action.h"

namespace AFR::VexU::base_action{
    template<typename T>
    class set_value_action : public action{
        T value_;
        void update_private(const double& delta_seconds) override;

    public:
        set_value_action(const scheduled_update_t& update_period, commandable& commandable, const T& value);
    };

    template<typename T>
    void set_value_action<T>::update_private(const double& delta_seconds){
        commandable_.set_value(std::any{value_});
    }

    template<typename T>
    set_value_action<T>::set_value_action(const scheduled_update_t& update_period, commandable& commandable,
                                          const T& value) : action(update_period, commandable), value_(value){}
}

#endif //VEX_U_2018_V5_SET_VALUE_H
