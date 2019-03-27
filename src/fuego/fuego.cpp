#include "afr-vexu-lib/ports_list.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-lib/afr-lib.h"
#include "afr-vexu-lib/afr-vexu-lib.h"

#include "fuego/fuego.h"
//#include "fuego/auto.h"
//#include "fuego/cap/cap.h"
#include "fuego/drive/drive.h"
#include "fuego/shooter/shooter.h"
#include "fuego/ball-intake/ball_intake.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Fuego{
    void init_robot(){
        try{
            init_lib();
            init_afr_vexu_lib();
            serial->enqueue_write(ODROID_ID,0,1);
            Shooter::init();
            Drive::init();
            BallIntake::init();

        }
        catch(std::exception& e){
            std::cerr << "Init error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"Init error"};
        }
        std::cout << "Initialization Complete" << std::endl;
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void op_control(){
        while(true){
            scheduled::update_all();
//            std::string line1 = "A: " + std::to_string(Cap::arm_encoder->get_position());
//            std::string line2 = "E: " + std::to_string(Cap::elbow_encoder->get_position());
//            std::string line3 = Cap::cap_state_machine->get_current_state()->get_name();
//            std::string other = "W: " + std::to_string(Cap::wrist_encoder->get_position());
//
//            while(line3.length() < 15){
//                line3 += " ";
//            }
//
//            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, line1.c_str());
//            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 0, line2.c_str());
//            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 2, 0, other.c_str());

            pros::delay(1);
        }
    }

    void disabled_robot(){

    }

    void destroy(){
        destroy_lib();
        destroy_afr_vexu_lib();
//        BaseReadable::destroy_battery();
//        BaseReadable::destroy_competition();
        //BaseReadable::destroy_controllers();
//        destroy_ports_list();

//        Drive::destroy();
        //Cap::destroy();
        //BallIntake::destroy();
//        Shooter::destroy();

    }

    void restart(){
//        destroy();
//        init_robot();
    }
}

#pragma clang diagnostic pop
