#ifndef VEX_U_2018_V5_AUTO_H
#define VEX_U_2018_V5_AUTO_H

#include "rev/cap/cap.h"
#include "rev/drive/drive.h"
#include "rev/shooter/shooter.h"

namespace AFR::VexU::Rev::Auto{
    const scheduled_update_t UPDATE_PERIOD = 10;

    const double PI = 3.14159265359;

    void init();
    void destroy();
    void reset();

    struct auto_meta {
        unsigned int timeout;
        unsigned int end_auto;
    };

    extern state_controller<auto_meta>* auto_controller;

}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
