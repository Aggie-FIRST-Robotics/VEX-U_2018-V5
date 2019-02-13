#include "robot/shooter/shooter.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/ports_list.h"
#include "robot/robot.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"
#include "robot/drive/drive.h"
#include "afr-vexu-lib/base-readable/motor_current_readable.h"
#include "afr-vexu-lib/base-readable/motor_temperature_readable.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot{
    BaseReadable::motor_temperature_readable* nautilus_temp = nullptr;
    BaseReadable::motor_current_readable* nautilus_current = nullptr;

    void init_robot(){
        try{
            nautilus_temp = new BaseReadable::motor_temperature_readable{NAUTILUS_MOTOR_PORT, "nautilus_temp"};
            nautilus_current = new BaseReadable::motor_current_readable{NAUTILUS_MOTOR_PORT, "nautilus_current"};

            BaseReadable::init_battery();
            std::cout << "Battery Initialized" << std::endl;
            BaseReadable::init_competition();
            std::cout << "Competition Initialized" << std::endl;

            init_ports_list();
            std::cout << "Ports List Initialized" << std::endl;

            //  Catapult::init();
            std::cout << "Catapult Initialized" << std::endl;
            //  Drive::init();
            std::cout << "Drive Initialized" << std::endl;
            Shooter::init();
            pros::lcd::initialize();
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

    void opcontrol_robot(){
        std::cout << "OPControl Begin" << std::endl;
        while(true){
            try{
                Catapult::catapult_subsystem->updateInputs();
                Drive::drive_subsystem->updateInputs();

                Catapult::catapult_subsystem->updateStates();
                Drive::drive_subsystem->updateStates();

                Catapult::catapult_subsystem->updateActions();
                Drive::drive_subsystem->updateActions();
//                std::cout << "Current drive state: "
//                          << Drive::drive_subsystem->get_state_machines().at(0)->get_current_state()->get_name()
//                          << std::endl;

                std::cout << "Temp: " << nautilus_temp->get_temperature() << ", Current: "
                        << nautilus_current->get_current() << std::endl;
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
        Drive::destroy();
    }

    void restart(){
        destroy();
        init_robot();
    }
}
#pragma clang diagnostic pop