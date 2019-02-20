#include "robot/shooter/shooter.h"
#include "display/lv_core/lv_style.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/ports_list.h"
#include "robot/robot.h"

#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/catapult/catapult.h"
#include "robot/drive/drive.h"
#include "robot/cap/cap.h"
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
            //std::cout << "Battery Initialized" << std::endl;
            BaseReadable::init_competition();
            // std::cout << "Competition Initialized" << std::endl;

            init_ports_list();
            //std::cout << "Ports List Initialized" << std::endl;

            Shooter::init();
            // std::cout << "Shooter  Initialized" << std::endl;
            //std::cout << "Catapult Initialized" << std::endl;
            Drive::init();
            //std::cout << "Drive Initialized" << std::endl;
            Cap::init();
            //std::cout << "Cap Initialized" << std::endl;

            //  do_screen_stuff();

//            if(!pros::lcd::initialize()){
//                throw std::runtime_error{"Cannot initialize lcd! " + std::to_string(pros::lcd::is_initialized())};
//            }
//            std::cout << "Current Limit: " << pros::c::motor_get_current_limit(NAUTILUS_MOTOR_PORT) << std::endl;
//            std::cout << "Voltage Limit: " << pros::c::motor_get_voltage_limit(NAUTILUS_MOTOR_PORT) << std::endl;
//            std::cout << (pros::c::motor_get_faults(NAUTILUS_MOTOR_PORT) & pros::E_MOTOR_FAULT_MOTOR_OVER_TEMP) << std::endl;
        }
        catch(std::exception& e){
            std::cerr << "Init error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"Init error"};
        }
        std::cout << "Initialization Complete" << std::endl;
        // opcontrol_robot();
    }

    void competition_init(){

    }

    void auto_robot(){

    }

    void opcontrol_robot(){
        std::cout << "OPControl Begin" << std::endl;
        while(true){
            try{
//                std::cout << 1;
                // Catapult::catapult_subsystem->updateInputs();
                // Drive::drive_subsystem->updateInputs();
                // std::cout<<"1"<<std::endl;
                Shooter::shooter_subsystem->updateInputs();
                // std::cout << "Shooter  input" << std::endl;
//                std::cout << 4;
                //Cap::cap_subsystem->updateInputs();

//                std::cout << 2;
                // Catapult::catapult_subsystem->updateStates();
                //   Drive::drive_subsystem->updateStates();
                //Cap::cap_subsystem->updateStates();
                //    std::cout<<"2"<<std::endl;
                Shooter::shooter_subsystem->updateStates();
                //  std::cout<<"3"<<std::endl;
                //  std::cout << "Shooter  state" << std::endl;
//                std::cout << 3;
                //Catapult::catapult_subsystem->updateActions();
                //Drive::drive_subsystem->updateActions();
                //Cap::cap_subsystem->updateActions();
                //     std::cout<<"4"<<std::endl;
                Shooter::shooter_subsystem->updateActions();
                // std::cout<<"5"<<std::endl;
                //  std::cout << "Shooter  Actions" << std::endl;

//                std::cout << "Current drive state: "
//                          << Drive::drive_subsystem->get_state_machines().at(0)->get_current_state()->get_name()
//                          << std::endl;

//                std::string temp = "Temperature: " + std::to_string(nautilus_temp->get_temperature());
//                std::string current = "Current:     " + std::to_string(nautilus_current->get_current());
//                pros::lcd::set_text(0, temp);
//                pros::lcd::set_text(1, current);
//                std::cout << temp << ", " << current << std::endl;



                /*   std::cout << Cap::cap_subsystem->get_state_machines().at(0)->get_current_state()->get_name()
                             << std::endl;*/
//                std::cout << std::endl;
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


        Shooter::destroy();
    }

    void restart(){
        destroy();
        init_robot();
    }

    void do_screen_stuff(){
//        lv_init();
//        lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
//        lv_label_set_text(title, "Test");
//        static lv_style_t text_style;
//        lv_style_copy(&text_style, &lv_style_plain);
//        text_style.text.color = LV_COLOR_WHITE;
//        lv_obj_set_style(title, &text_style);
//        lv_obj_align(title, nullptr, LV_ALIGN_IN_TOP_MID, 0, 50);
    }
}
#pragma clang diagnostic pop