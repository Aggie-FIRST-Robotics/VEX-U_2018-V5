#include "robot/robot.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"
#include "robot/drive/drive.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot{
    void init_robot(){
        try{
            BaseReadable::Controller::init();

            Catapult::init();
            Drive::init();
        }
        catch(std::exception& e){
            std::cerr << "Init error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"Init error"};
        }
        pros::lcd::initialize();
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void opcontrol_robot(){
        try{
            ordered_input* nautilus_encoder = nullptr;
            state_controller* state = nullptr;
            readable* readable1 = nullptr;

            Catapult::catapult_subsystem->get_input("nautilus_encoder");
            nautilus_encoder->get_input(readable1);
            auto* motor_encoder_readable = (BaseReadable::motor_encoder_readable*) readable1;
            double position = 0;
            while(true){
                Catapult::catapult_subsystem->get_state_machine(<#initializer#>);
//                std::cout << "State: " << state;
//                motor_encoder_readable->get_position(position);
                pros::lcd::print(1, std::to_string(position).c_str());

                BaseReadable::Controller::update();
                Catapult::catapult_subsystem->updateInputs();
//                Drive::drive_subsystem->updateInputs();

                Catapult::catapult_subsystem->updateStates();
//                Drive::drive_subsystem->updateStates();

                Catapult::catapult_subsystem->updateActions();
//                Drive::drive_subsystem->updateActions();

            }
        }
        catch(std::exception& e){
            std::cerr << "OpControl error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"OpControl error"};
        }
    }

    void disabled_robot(){

    }

    void destroy(){
        BaseReadable::Controller::destroy();

        Catapult::destroy();
    }

    void restart(){
        destroy();
        init_robot();
    }
}
#pragma clang diagnostic pop