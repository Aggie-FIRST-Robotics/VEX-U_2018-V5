#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "fuego/fuego.h"
#include "afr-lib/state_controller.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/comms/serial_manager.h"
#include "afr-vexu-lib/auto-drive/auto_drive.h"

namespace AFR::VexU::Fuego::Drive{

	struct drive_meta {};

    static constexpr scheduled_update_t UPDATE_PERIOD = 10;
    static constexpr double TICKS_TO_IN = 0.013963;
    static constexpr double PROS_TO_IN_VEL = 0.069813;
    static constexpr double PI = 3.14159265359;

    const bool DIRECTION = true;

    extern AutoDrive::auto_drive* auto_drivetrain;
    extern state_controller<drive_meta>* drive_machine;
    extern state* manual;
    extern state* autonomous;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_DRIVE_H
