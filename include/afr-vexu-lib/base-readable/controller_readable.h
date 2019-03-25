#ifndef VEX_U_2018_V5_CONTROLLER_READABLE_H
#define VEX_U_2018_V5_CONTROLLER_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable{
    class controller_readable : public virtual nameable {
        pros::controller_id_e_t controller_;

    public:
        explicit controller_readable(pros::controller_id_e_t controller);

        bool is_digital_pressed(pros::controller_digital_e_t button);
        int32_t get_analog(pros::controller_analog_e_t stick);
    };

    extern controller_readable* driver_controller;
    extern controller_readable* operator_controller;

    void init_controllers();
    void destroy_controllers();

}

#endif //VEX_U_2018_V5_CONTROLLER_READABLE_H
