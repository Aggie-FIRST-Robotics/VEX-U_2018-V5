#ifndef VEX_U_2018_V5_DRIVE_H
#define VEX_U_2018_V5_DRIVE_H

#include "rev/rev.h"
#include "afr-lib/state_controller.h"

#include "rev/drive/base/base.h"
#include "rev/drive/shifter/shifter.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::Rev::Drive{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const double LOW_TO_HIGH_SPEED_THRESHOLD = 100;
    const double HIGH_TO_LOW_SPEED_THRESHOLD = 100;

    const double SHIFTER_LOW_GEAR_TARGET = 600;  
    const double SHIFTER_HIGH_GEAR_TARGET = 100;

    const int16_t SHIFTER_VOLTAGE = 200;

    void init();
    void destroy();
}

#endif //VEX_U_2018_V5_DRIVE_H
