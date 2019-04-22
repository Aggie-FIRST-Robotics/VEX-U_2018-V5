#ifndef VEX_U_2018_V5_AUTO_H
#define VEX_U_2018_V5_AUTO_H

#include "rev/cap/cap.h"
#include "rev/drive/drive.h"
#include "rev/shooter/shooter.h"

namespace AFR::VexU::Rev::Auto{
    const scheduled_update_t UPDATE_PERIOD = 10;

    void init();
    void destroy();

}

#endif //VEX_U_2018_V5_BALL_INTAKE_H
