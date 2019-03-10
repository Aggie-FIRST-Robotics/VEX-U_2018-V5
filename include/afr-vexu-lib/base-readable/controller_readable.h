#ifndef VEX_U_2018_V5_CONTROLLER_READABLE_H
#define VEX_U_2018_V5_CONTROLLER_READABLE_H

#include <unordered_map>

#include <main.h>

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable{
    class controller_readable : public virtual nameable {
        pros::controller_id_e_t controller_;

    public:
        explicit controller_readable(pros::controller_id_e_t controller);
        
        bool get_A();
        bool get_B();
        bool get_X();
        bool get_Y();
        bool get_UP();
        bool get_DOWN();
        bool get_LEFT();
        bool get_RIGHT();
        bool get_L1();
        bool get_L2();
        bool get_R1();
        bool get_R2();
        int32_t get_left_x();
        int32_t get_left_y();
        int32_t get_right_x();
        int32_t get_right_y();
        
    };

    extern controller_readable* driver_controller;
    extern controller_readable* operator_controller;

    void init_controllers();
    void destroy_controllers();

}

#endif //VEX_U_2018_V5_CONTROLLER_READABLE_H
