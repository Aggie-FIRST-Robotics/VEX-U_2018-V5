#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "rev/rev.h"
#include "afr-lib/state_controller.h"

#include "rev/cap/arm/arm.h"
#include "rev/cap/wrist/wrist.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::Rev::Cap{

    const scheduled_update_t UPDATE_PERIOD = 10;

    //Down
    const double ARM_GROUND_POSITION = 0;

    //Flip Low
    const double ARM_FLIP_LOW_POSITION = 500;

    //Descore Prime
    const double ARM_DESCORE_PRIME_POSITION = 4600;

    //Score
    const double ARM_SCORE_POSITION = 4600;

    //Score Prime
    const double ARM_SCORE_PRIME_POSITION = 4050;

    //Wrist
    const double WRIST_FLIP_POSITION = 750;

    const double PID_TOLERANCE = 100;
    const int16_t INTAKE_VOLTAGE = 12000;
    const int16_t IDLE_VOLTAGE = 3000;

    const double ANGLE_ARM_TARGET = 850;
    const double ANGLE_ELBOW_TARGET = 5850;

    void init();

    struct cap_arm_meta{
        bool is_stealing;

        cap_arm_meta(){
            is_stealing = false;
        }

        explicit cap_arm_meta(bool is_stealing){
            this->is_stealing = is_stealing;
        };

    };

    /////State Controlle
    extern state_controller<cap_arm_meta>* cap_arm;

    /////States
    extern state* zero_arm;
    extern state* ground;
    extern state* flip;
    extern state* score_prime;
    extern state* score_flip;
    extern state* score;
    extern state* descore_prime;
}

#endif //VEX_U_2018_V5_CAP_H
