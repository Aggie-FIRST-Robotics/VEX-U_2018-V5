#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "robot/robot.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/adi_digital_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::Robot::Drive {

    const scheduled_update_t START_TOPLEFTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_UPDATE_PERIOD = 100;
    const scheduled_update_t START_TOPRIGHTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_BOTTOMLEFTMOTOR_UPDATE_PERIOD = 100;
    const scheduled_update_t START_BOTTOMRIGHTMOTOR_UPDATE_PERIOD = 100;
    extern subsystem_controller *drive_subsystem;


    void init();

    void arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_);

    void destroy();


}

#endif //VEX_U_2018_V5_DRIVE_H
