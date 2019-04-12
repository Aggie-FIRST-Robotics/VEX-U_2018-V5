#ifndef VEX_U_2018_V5_CAP_2_H
#define VEX_U_2018_V5_CAP_2_H

#include "fuego/fuego.h"
#include "afr-lib/state_controller.h"

#include "fuego/cap/arm/arm.h"
#include "fuego/cap/elbow/elbow.h"
#include "fuego/cap/wrist/wrist.h"

#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::Fuego::Cap{
    const scheduled_update_t UPDATE_PERIOD = 10;

    //Down
    const double ARM_GROUND_POSITION = 0;
    const double ELBOW_GROUND_POSITION = 2950;

    //Flip Low
    const double ARM_FLIP_LOW_POSITION = 370;

    //Hold
    const double ELBOW_STORE_POSITION = 450;

    //Flip High
    const double ELBOW_FLIP_HIGH_POSITION = 850;

    //Descore Prime
    const double ARM_DESCORE_PRIME_POSITION = 1550;
    const double ELBOW_DESCORE_PRIME_POSITION = -560;

    //Score
    const double ARM_SCORE_POSITION = 2100;
    const double ELBOW_SCORE_POSITION = -560;

    //Score Prime
    const double ARM_SCORE_PRIME_POSITION = 2100;
    const double ELBOW_SCORE_PRIME_POSITION = 460;

    //Wrist
    const double WRIST_FLIP_POSITION = 750;

    const double PID_TOLERANCE = 100;
    const int16_t INTAKE_VOLTAGE = 12000;
    const int16_t IDLE_VOLTAGE = 3000;

    const double ANGLE_ARM_TARGET = 430;
    const double ANGLE_ELBOW_TARGET = 5850;

    //AUTO SET POINT
    const double ARM_ANGLE_PICKUP = 970;
    const double ELBOW_ANGLE_PICKUP = 6000;

    void init();

    struct cap_arm_meta{
        bool is_stealing;
    };

    extern state_controller<cap_arm_meta>* cap_arm;

    extern state* zero_arm;
    extern state* zero_elbow;
    extern state* store;
    extern state* ground;
    extern state* flip_low;
    extern state* flip_high;
    extern state* score_prime;
    extern state* score_flip;
    extern state* score;
    extern state* descore_prime;
    extern state* dick;
    extern state* ascend_prime;
    extern state* ascend;
    extern state* angled_pickup;
}

#endif //VEX_U_2018_V5_CAP_H
