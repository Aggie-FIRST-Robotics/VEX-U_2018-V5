#include "robot/robot.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot{
    void init_robot(){
        BaseReadable::Controller::init();

        Catapult::init();
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void opcontrol_robot(){
        while(true){
            BaseReadable::Controller::update();
            Catapult::catapult_subsystem->updateInputs();

            Catapult::catapult_subsystem->updateStates();

            Catapult::catapult_subsystem->updateActions();
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