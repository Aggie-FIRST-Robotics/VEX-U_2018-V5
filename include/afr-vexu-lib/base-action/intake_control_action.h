#ifndef VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H
#define VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H


#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/action.h"


namespace AFR::VexU::BaseAction {
    class intake_control_action : public action {
        int16_t outtake_val_, intake_val_, hold_val_;
        AFR::VexU::BaseReadable::controller_digital_readable* intake_button_;
        AFR::VexU::BaseReadable::controller_digital_readable* outtake_button_;

        void update_private(const double &delta_seconds) override;

    public:
        /**
         * Creates a set value action
         * @param update_period passed to scheduled
         * @param commandable the commandable to set
         * @param readable to be used
         * @param second readable to be used
         * @param name error_t value if error encountered
         */
        intake_control_action(const AFR::VexU::scheduled_update_t& update_period, AFR::VexU::commandable* commandable,
                              AFR::VexU::BaseReadable::controller_digital_readable* outtake_button,
                              AFR::VexU::BaseReadable::controller_digital_readable* intake_button, int16_t outtake_val,
                              int16_t intake_val, int16_t hold_val, const std::string& name);


    };
}

#endif //VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H