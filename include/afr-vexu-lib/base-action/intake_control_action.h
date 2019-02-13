#ifndef VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H
#define VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H


#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/action.h"


namespace AFR::VexU::BaseAction {
    class intake_control_action : public action {


        AFR::VexU::BaseReadable::controller_digital_readable *right_;
        AFR::VexU::BaseReadable::controller_digital_readable *left_;

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
        intake_control_action(const scheduled_update_t &update_period, commandable *commandable,
                      BaseReadable::controller_digital_readable *left, BaseReadable::controller_digital_readable *right,
                      const std::string &name);


    };
}

#include "intake_control_action.cpp"

#endif //VEX_U_2018_V5_INTAKE_CONTROL_ACTION_H