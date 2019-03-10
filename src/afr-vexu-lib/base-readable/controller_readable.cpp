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


    bool controller_readable::get_A(){
        return pros::c::controller_get_digital(controller_, DIGITAL_A) == 1;
    }
    
    bool controller_readable::get_B(){
        return pros::c::controller_get_digital(controller_, DIGITAL_B) == 1;
    }
    
    bool controller_readable::get_X(){
        return pros::c::controller_get_digital(controller_, DIGITAL_X) == 1;
    }
    
    bool controller_readable::get_Y(){
        return pros::c::controller_get_digital(controller_, DIGITAL_Y) == 1;
    }
    
    bool controller_readable::get_UP(){
        return pros::c::controller_get_digital(controller_, DIGITAL_UP) == 1;
    }
    
    bool controller_readable::get_DOWN(){
        return pros::c::controller_get_digital(controller_, DIGITAL_DOWN) == 1;
    }
    
    bool controller_readable::get_LEFT(){
        return pros::c::controller_get_digital(controller_, DIGITAL_LEFT) == 1;
    }
    
    bool controller_readable::get_RIGHT(){
        return pros::c::controller_get_digital(controller_, DIGITAL_RIGHT) == 1;
    }
    
    bool controller_readable::get_L1(){
        return pros::c::controller_get_digital(controller_, DIGITAL_L1) == 1;
    }
    
    bool controller_readable::get_L2(){
        return pros::c::controller_get_digital(controller_, DIGITAL_L2) == 1;
    }
    
    bool controller_readable::get_R1(){
        return pros::c::controller_get_digital(controller_, DIGITAL_R1) == 1;
    }
    
    bool controller_readable::get_R2(){
        return pros::c::controller_get_digital(controller_, DIGITAL_R2) == 1;
    }
    
    int32_t controller_readable::get_left_x(){
        return pros::c::controller_get_analog(controller_, ANALOG_LEFT_X);
    }
    
    int32_t controller_readable::get_left_y(){
        return pros::c::controller_get_analog(controller_, ANALOG_LEFT_Y);
    }
    
    int32_t controller_readable::get_right_x(){
        return pros::c::controller_get_analog(controller_, ANALOG_RIGHT_X);
    }
    
    int32_t controller_readable::get_right_y(){
        return pros::c::controller_get_analog(controller_, ANALOG_RIGHT_Y);
    }

}
