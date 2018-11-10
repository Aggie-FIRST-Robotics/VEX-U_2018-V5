#ifndef VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H
#define VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    template<typename T>
    class equivalent_value_action : public action{
        const T* value_ptr_;
        void update_private(const double& delta_seconds) override;

    public:
        equivalent_value_action(const scheduled_update_t& update_period, commandable& commandable, const T* value_ptr);
    };

    template<typename T>
    void equivalent_value_action<T>::update_private(const double& delta_seconds){
        commandable_.set_value(std::any{*value_ptr_});
    }

    template<typename T>
    equivalent_value_action<T>::equivalent_value_action(const scheduled_update_t& update_period,
                                                        commandable& commandable, const T*) : action(update_period,
                                                                                                     commandable),
                                                                                              value_ptr_(value_ptr_){}
}

#endif //VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H
