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
            std::cout << "Battery Initialized" << std::endl;
            BaseReadable::init_competition();
            std::cout << "Competition Initialized" << std::endl;

            init_ports_list();
            std::cout << "Ports List Initialized" << std::endl;

            Catapult::init();
            std::cout << "Catapult Initialized" << std::endl;
            Drive::init();
            std::cout << "Drive Initialized" << std::endl;
            Cap::init();
            std::cout << "Cap Initialized" << std::endl;

            do_screen_stuff();

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
    }

    void competition_init(){

    }

    void auto_robot(){
        std::cout << "Got to auto!" << std::endl;
        while(true){
            robot_auto_subsystem->updateInputs();
            robot_auto_subsystem->updateStates();
            robot_auto_subsystem->updateActions();

            std::string line1 = robot_auto_subsystem->get_state_machines().at(0)->get_current_state()->get_name();
            while(line1.length() < 15){
                line1 += " ";
            }
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, line1.c_str());
        }
    }

    void opcontrol_robot(){
        std::cout << "OPControl Begin" << std::endl;
        while(true){
            try{
//                std::cout << 1;
                Catapult::catapult_subsystem->updateInputs();
                Drive::drive_subsystem->updateInputs();
//                std::cout << 4;
                Cap::cap_subsystem->updateInputs();

//                std::cout << 2;
                Catapult::catapult_subsystem->updateStates();
                Drive::drive_subsystem->updateStates();
                Cap::cap_subsystem->updateStates();

//                std::cout << 3;
                Catapult::catapult_subsystem->updateActions();
                Drive::drive_subsystem->updateActions();
                Cap::cap_subsystem->updateActions();
//                std::cout << "Current drive state: "
//                          << Drive::drive_subsystem->get_state_machines().at(0)->get_current_state()->get_name()
//                          << std::endl;

//                std::string temp = "Temperature: " + std::to_string(nautilus_temp->get_temperature());
//                std::string current = "Current:     " + std::to_string(nautilus_current->get_current());
//                pros::lcd::set_text(0, temp);
//                pros::lcd::set_text(1, current);
//                std::cout << temp << ", " << current << std::endl;
//                std::cout << Cap::cap_subsystem->get_state_machines().at(0)->get_current_state()->get_name()
//                          << std::endl;
//                std::cout << std::endl;

                std::string line_1_text = std::string("E: ") + std::to_string(Cap::elevator_encoder->get_position());
                std::string line_2_text = std::string("A: ") + std::to_string(Cap::arm_encoder->get_position());
                std::string line_3_text = Cap::cap_subsystem->get_state_machines().at(
                        0)->get_current_state()->get_name();
                while(line_3_text.size() < 15){
                    line_3_text += " ";
                }

                pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, line_1_text.c_str());
                pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 0, line_2_text.c_str());
                pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 2, 0, line_3_text.c_str());
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
        //BaseReadable::destroy_controllers();
        destroy_ports_list();

        Catapult::destroy();
        Drive::destroy();
        //Cap::destroy();
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