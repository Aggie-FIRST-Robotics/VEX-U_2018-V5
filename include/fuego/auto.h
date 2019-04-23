#ifndef VEX_U_2018_V5_AUTO_H
#define VEX_U_2018_V5_AUTO_H

#include "fuego/cap/cap.h"
#include "fuego/drive/drive.h"
#include "fuego/shooter/shooter.h"
#include "fuego/ball-intake/ball_intake.h"

namespace AFR::VexU::Fuego::Auto{
    const scheduled_update_t UPDATE_PERIOD = 10;

    void init();
    void destroy();

    struct auto_meta {
        unsigned int timeout;
        unsigned int end_auto;
    };

    extern state_controller<auto_meta>* auto_controller;

}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
