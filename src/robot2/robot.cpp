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
            //Cap::cap_subsystem->updateInputs();

            //Cap::cap_subsystem->updateStates();

            //Cap::cap_subsystem->updateActions();
        }
    }
}

#pragma clang diagnostic pop