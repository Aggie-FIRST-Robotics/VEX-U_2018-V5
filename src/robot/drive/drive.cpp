
#include <robot/drive/drive.h>

#include "robot/drive/drive.h"

namespace AFR::VexU::Robot::Drive {
    drive::drive(){

    }


    void drive::arcadedrive(const std::int32_t &leftpower_, const std::int32_t &rightpower_) {
        topleftmotor.set_value(rightpower_ - leftpower_);
        bottomleftmotor.set_value(rightpower_ - leftpower_);
        toprightmotor.set_value(rightpower_ + leftpower_);
        bottomrightmotor.set_value(rightpower_ + leftpower_);
    }

    void init() {
        topleftmotor = BaseCommandable::motor_commandable{LEFT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        toprightmotor = BaseCommandable::motor_commandable{RIGHT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        bottomleftmotor = BaseCommandable::motor_commandable{LEFT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};
        bottomrightmotor = BaseCommandable::motor_commandable{RIGHT_RAIL_MOTOR_B_PROT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_BRAKE_BRAKE, nullptr};


        AFR::VexU::Robot::BaseAction::set_value_action<int> stop_action_int{800, int_motor, 0};




    }

};



