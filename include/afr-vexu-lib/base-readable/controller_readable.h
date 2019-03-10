#ifndef VEX_U_2018_V5_CONTROLLER_READABLE_H
#define VEX_U_2018_V5_CONTROLLER_READABLE_H

#include <unordered_map>

#include "main.h"

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable{
    class controller_readable : public virtual nameable {
        pros::controller_id_e_t controller_;

    public:
        controller_readable(pros::controller_id_e_t controller, const std::string& name);
        
        bool get_a();
        bool get_b();
        bool get_x();
        bool get_y();
        bool get_up();
        bool get_down();
        bool get_left();
        bool get_right();
        bool get_l1();
        bool get_l2();
        bool get r1();
        bool get_r2();
        int32_t get_left_x();
        int32_t get_left_y();
        int32_t get_right_x();
        int32_t get_right_y();
        
    };

}

#endif //VEX_U_2018_V5_CONTROLLER_READABLE_H
