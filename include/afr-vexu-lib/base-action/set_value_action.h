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
        void update_private(const double& delta_seconds) override;

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
}

#include "afr-vexu-lib/base-action/set_value_action.cpp"

#endif //VEX_U_2018_V5_SET_VALUE_H
