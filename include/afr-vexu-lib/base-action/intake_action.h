#ifndef VEX_U_2018_V5_SET_VALUE_H
#define VEX_U_2018_V5_SET_VALUE_H

#include "afr-vexu-lib/action.h"

namespace AFR::VexU::BaseAction{
    /**
     * An action that sets a commandable to an input
     * @tparam T the type of constant value
     */
    template<typename T>
    class intake_action : public action{
        T value_;
        pros::controller_digital_e_t input_1_;
        pros::controller_digital_e_t input_2_;
        error_t update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a set input action
         * @param update_period passed to scheduled
         * @param commandable the commandable to set
         * @param input the first input to be set
         * @param input the second input to be set
         * @param result error_t value if error encountered
         */
        intake_action(const scheduled_update_t& update_period, commandable& commandable,
                      const pros::controller_digital_e_t& input_1, const pros::controller_digital_e_t& input_2
                      error_t* result = nullptr);

        error_t check_buttons();

        error_t set_inputs(const pros::controller_digital_e_t& input_1_, const pros::controller_digital_e_t& input_2_);
    };
}

#include "afr-vexu-lib/base-action/intake_action.cpp"

#endif //VEX_U_2018_V5_SET_VALUE_H
