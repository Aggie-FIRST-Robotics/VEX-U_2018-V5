#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "rev/rev.h"
#include "afr-lib/state_controller.h"

#include "rev/drive/base/base.h"
#include "rev/drive/shifter/shifter.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"
#include "afr-vexu-lib/auto-drive/auto_drive.h"

namespace AFR::VexU::Rev::Drive{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const double LOW_TO_HIGH_SPEED_THRESHOLD = 100;
    const double HIGH_TO_LOW_SPEED_THRESHOLD = 100;

    const double SHIFTER_LOW_GEAR_TARGET = 600;  
    const double SHIFTER_HIGH_GEAR_TARGET = 100;

    const int16_t SHIFTER_VOLTAGE = 200;

    void init();
    void destroy();

    struct drive_meta {};

    /////State Controller
    extern state_controller<drive_meta>* drive_machine;

    /////States
    extern state* low_gear;
    extern state* high_gear;
    extern state* autonomous;

    extern AutoDrive::auto_drive* auto_drivetrain;
}

#endif //VEX_U_2018_V5_DRIVE_H
