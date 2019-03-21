
#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::BaseReadable{

    controller_readable* driver_controller = nullptr;
    controller_readable* operator_controller = nullptr;

    void init_controllers() {
        driver_controller = new controller_readable(pros::E_CONTROLLER_MASTER);
        operator_controller = new controller_readable(pros::E_CONTROLLER_PARTNER);
    }

    void destroy_controllers() {
        delete driver_controller;
        delete operator_controller;
    }

    controller_readable::controller_readable(pros::controller_id_e_t controller)
            : nameable(controller == pros::E_CONTROLLER_MASTER ? "driver_controller" : "operator_controller"),
              controller_(controller){}

    bool controller_readable::is_digital_pressed(pros::controller_digital_e_t button){
        return pros::c::controller_get_digital(controller_, button) == 1;
    }

    int32_t controller_readable::get_analog(pros::controller_analog_e_t stick){
        return pros::c::controller_get_analog(controller_, stick);
    }
}
