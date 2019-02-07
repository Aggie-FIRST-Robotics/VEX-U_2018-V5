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
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void opcontrol_robot(){
        try{
            while(true){
                BaseReadable::Controller::update();
                Catapult::catapult_subsystem->updateInputs();
                Drive::drive_subsystem->updateInputs();

                Catapult::catapult_subsystem->updateStates();
                Drive::drive_subsystem->updateStates();

                Catapult::catapult_subsystem->updateActions();
                Drive::drive_subsystem->updateActions();
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