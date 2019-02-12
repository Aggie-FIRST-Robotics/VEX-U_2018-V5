#ifndef VEX_U_2018_V5_CATAPULT_H
#define VEX_U_2018_V5_CATAPULT_H

#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot::Catapult{
    const scheduled_update_t HOLD_NAUTILUS_UPDATE_PERIOD = 10;
    const scheduled_update_t COCK_NAUTILUS_UPDATE_PERIOD = 10;
    const scheduled_update_t STOP_NAUTILUS_UPDATE_PERIOD = 10;
    const scheduled_update_t FIRE_NAUTILUS_UPDATE_PERIOD = 10;

    const scheduled_update_t CATAPULT_UPDATE_PERIOD = 10;

    const double NAUTILUS_FIRE_THRESHOLD = 360;
    const scheduled_update_t NAUTILUS_STOP_TIME = 250;

    //Subsystem controller
    extern subsystem_controller* catapult_subsystem;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_CATAPULT_H
