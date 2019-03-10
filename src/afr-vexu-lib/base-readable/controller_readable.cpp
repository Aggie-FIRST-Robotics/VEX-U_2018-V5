#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::BaseReadable{

    controller_readable::controller_readable(pros::controller_id_e_t controller)
            : nameable(controller == pros::E_CONTROLLER_MASTER ? "driver_controller" : "operator_controller"),
              controller_(controller){}


    bool controller_readable::get_a(){
        return pros::c::controller_get_digital(controller_, DIGITAL_A);
    }
    
    bool controller_readable::get_b(){
        return pros::c::controller_get_digital(controller_, DIGITAL_B);
    }
    
    bool controller_readable::get_x(){
        return pros::c::controller_get_digital(controller_, DIGITAL_X);
    }
    
    bool controller_readable::get_y(){
        return pros::c::controller_get_digital(controller_, DIGITAL_Y);
    }
    
    bool controller_readable::get_up(){
        return pros::c::controller_get_digital(controller_, DIGITAL_UP);
    }
    
    bool controller_readable::get_down(){
        return pros::c::controller_get_digital(controller_, DIGITAL_DOWN);
    }
    
    bool controller_readable::get_left(){
        return pros::c::controller_get_digital(controller_, DIGITAL_LEFT);
    }
    
    bool controller_readable::get_right(){
        return pros::c::controller_get_digital(controller_, DIGITAL_RIGHT);
    }
    
    bool controller_readable::get_l1(){
        return pros::c::controller_get_digital(controller_, DIGITAL_L1);
    }
    
    bool controller_readable::get_l2(){
        return pros::c::controller_get_digital(controller_, DIGITAL_L2);
    }
    
    bool controller_readable::get_r1(){
        return pros::c::controller_get_digital(controller_, DIGITAL_R1);
    }
    
    bool controller_readable::get_r2(){
        return pros::c::controller_get_digital(controller_, DIGITAL_R2);
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
