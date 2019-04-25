#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"

#include "rev/rev.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Rev{
    void init_robot(){
        try{
            init_lib();
            init_afr_vexu_lib();
            serial->enqueue_write(ODROID_ID, 0, 1);
            Shooter::init();
            Drive::init();
            //BallIntake::init();
            Cap::init();
            Cap::Arm::encoder->tare_position();
            Auto::init();
            Auto::auto_controller->disable();
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
        Auto::auto_controller->metadata().end_auto = pros::millis() + 45000;
        Auto::auto_controller->enable();
        Auto::reset();
        while(true){
            scheduled::update_all();
            pros::delay(1);

            std::string text = Cap::cap_arm->get_current_state_name();
            while(text.size() < 10){
                text += " ";
            }
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, text.c_str());
        }
    }

    void op_control(){
        Auto::auto_controller->disable();
        Shooter::reset();
        Shooter::shooter_state_controller->set_state(Shooter::set_point);
        Cap::cap_arm->set_state(Cap::ground);
        Drive::drive_machine->set_state(Drive::high_gear);
        while(true){
            scheduled::update_all();
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
        //memes
    }
}

#pragma clang diagnostic pop

#pragma clang diagnostic pop