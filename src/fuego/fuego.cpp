#include "afr-vexu-lib/ports_list.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-lib/afr-lib.h"
#include "afr-vexu-lib/afr-vexu-lib.h"

#include "fuego/fuego.h"
//#include "fuego/auto.h"
//#include "fuego/cap/cap.h"
//#include "fuego/drive/drive.h"
#include "fuego/shooter/shooter.h"
//#include "fuego/ball-intake/ball_intake.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Fuego{
    void init_robot(){
        try{
            init_lib();
            init_afr_vexu_lib();
            Shooter::init();

//            Drive::init();
//            std::cout << "Drive Initialized" << std::endl;
//            BallIntake::init();
//            std::cout << "Ball Intake Initialized" << std::endl;
//            Cap::init();
//            std::cout << "Cap Initialized" << std::endl;
//            Shooter::init();
//            std::cout << "Shooter Initialized" << std::endl;


            //init_auto();
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
            //std::cout << "Main" << std::endl;
            //serial->enqueue_write(ODROID_ID,1,10);
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

//            Cap::cap_subsystem->updateInputs();
//            Drive::drive_subsystem->updateInputs();
//            BallIntake::ball_intake_subsystem->updateInputs();
//            Shooter::shooter_subsystem->updateInputs();
//
//            Cap::cap_subsystem->updateStates();
//            Drive::drive_subsystem->updateStates();
//            BallIntake::ball_intake_subsystem->updateStates();
//            Shooter::shooter_subsystem->updateStates();

//            Cap::cap_subsystem->updateActions();
//            Drive::drive_subsystem->updateActions();
//            BallIntake::ball_intake_subsystem->updateActions();
//            Shooter::shooter_subsystem->updateActions();
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
