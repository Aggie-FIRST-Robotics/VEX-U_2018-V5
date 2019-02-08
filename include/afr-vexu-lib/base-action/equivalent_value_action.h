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
        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a equivalent value action
         * @param update_period passed to scheduled
         * @param commandable passed to action
         * @param value_ptr the pointer to the value to be copied every update
         * @param name error_t value if error encountered
         */
        equivalent_value_action(scheduled_update_t update_period, commandable* commandable, const T* value_ptr,
                                const std::string& name);
    };
}

#include "equivalent_value_action.cpp"

#endif //VEX_U_2018_V5_EQUIVALENT_VALUE_ACTION_H
