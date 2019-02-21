#include "afr-vexu-lib/ports_list.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "robot2/robot.h"

#include "robot2/cap/cap.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot2{
    void init_robot(){
        BaseReadable::init_battery();
        std::cout << "Battery Initialized" << std::endl;
        BaseReadable::init_competition();
        std::cout << "Competition Initialized" << std::endl;

        init_ports_list();
        std::cout << "Ports List Initialized" << std::endl;

        Cap::init();
    }

    void op_control(){
        while(true){
            std::string line1 = "A: " + std::to_string(Cap::arm_encoder->get_position());
            std::string line2 = "E: " + std::to_string(Cap::elbow_encoder->get_position());
            std::string line3 = Cap::cap_state_machine->get_current_state()->get_name();

            while(line3.length() < 15){
                line3 += " ";
            }

            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, line1.c_str());
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 0, line2.c_str());
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 2, 0, line3.c_str());

            Cap::cap_subsystem->updateInputs();

            Cap::cap_subsystem->updateStates();

            Cap::cap_subsystem->updateActions();

//            if(pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_A)){
//                Cap::arm_encoder->tare_position();
//            }
//            if(pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_B)){
//                Cap::elbow_encoder->tare_position();
//            }
        }
    }
}

#pragma clang diagnostic pop
