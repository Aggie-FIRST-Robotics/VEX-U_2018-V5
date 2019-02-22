#ifndef VEX_U_2018_V5_AUTO_H
#define VEX_U_2018_V5_AUTO_H

#include "afr-vexu-lib/subsystem_controller.h"

namespace AFR::VexU::Robot2{
    extern subsystem_controller* robot2_auto_subsystem;

    const double DRIVE_FORWARD_TARGET = 10000;

    void init_auto();
}

#endif //VEX_U_2018_V5_AUTO_H
