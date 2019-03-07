#ifndef VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H
#define VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/action.h"

namespace AFR::VexU::Robot2::Drive{
    class arcade_drive_action : public action{
        bool is_right;
        BaseReadable::controller_analog_readable* right_stick_;
        BaseReadable::controller_analog_readable* left_stick_;


        void update_private(const double& delta_seconds) override;

    public:
        arcade_drive_action(scheduled_update_t update_period, commandable* commandable,
                            BaseReadable::controller_analog_readable* left_stick,
                            BaseReadable::controller_analog_readable* right_stick, bool is_right,
                            const std::string& name);
    };
}

#endif //VEX_U_2018_V5_ARCADE_DRIVE_ACTION_H
