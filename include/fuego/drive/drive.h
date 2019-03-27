#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "fuego/fuego.h"
#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"

namespace AFR::VexU::Fuego::Drive{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const bool DIRECTION = false;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_DRIVE_H
