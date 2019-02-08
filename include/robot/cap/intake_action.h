//
// Created by aamhi on 2/6/2019.
//
#include <afr-vexu-lib/base-readable/controller_readable.h>
#include "afr-vexu-lib/action.h"




#ifndef VEX_U_2018_V5_INTAKE_ACTION_H
#define VEX_U_2018_V5_INTAKE_ACTION_H

#endif //VEX_U_2018_V5_INTAKE_ACTION_H

namespace AFR::VexU::Robot::Cap {

    class intake_action : public action {


        AFR::VexU::BaseReadable::controller_digital_readable *right_;
        AFR::VexU::BaseReadable::controller_digital_readable *left_;

        void update_private(const double &delta_seconds) override;

    public:
        intake_action(const scheduled_update_t &update_period, commandable *commandable,
                      BaseReadable::controller_digital_readable *left, BaseReadable::controller_digital_readable *right,
                      const std::string &name);


    };
}