#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/ports_list.h"
#include "robot/robot.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"
#include "robot/drive/drive.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot{
    void init_robot(){
        try{
            BaseReadable::init_battery();
            BaseReadable::init_competition();

            init_ports_list();

            Catapult::init();
            Drive::init();

            pros::lcd::initialize();
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
        while(true){
            try{
                Catapult::catapult_subsystem->updateInputs();
                Drive::drive_subsystem->updateInputs();

                Catapult::catapult_subsystem->updateStates();
                Drive::drive_subsystem->updateStates();

                Catapult::catapult_subsystem->updateActions();
                Drive::drive_subsystem->updateActions();
            }
            catch(std::exception& e){
                std::cerr << "OpControl error" << std::endl;
                std::cerr << e.what() << std::endl;

                throw std::runtime_error{"OpControl error"};
            }
        }

    }

    void disabled_robot(){

    }

    void destroy(){
        BaseReadable::destroy_battery();
        BaseReadable::destroy_competition();
        BaseReadable::destroy_controllers();
        destroy_ports_list();

        Catapult::destroy();
    }

    void restart(){
        destroy();
        init_robot();
    }
}
#pragma clang diagnostic pop