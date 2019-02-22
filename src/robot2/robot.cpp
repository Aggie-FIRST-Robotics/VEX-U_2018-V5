#include "afr-vexu-lib/ports_list.h"
#include "afr-vexu-lib/SerialManager.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "robot2/robot.h"
#include "robot2/auto.h"

#include "robot2/cap/cap.h"
#include "robot2/drive/drive.h"
#include "robot2/shooter/shooter.h"
#include "robot2/ball-intake/ball_intake.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace AFR::VexU::Robot2{
    void init_robot(){
        try{
            // init_serial_manager(1);
            // std::cout << "Serial Manager Initialized" << std::endl;

            BaseReadable::init_battery();
            std::cout << "Battery Initialized" << std::endl;
            BaseReadable::init_competition();
            std::cout << "Competition Initialized" << std::endl;

            init_ports_list();
            std::cout << "Ports List Initialized" << std::endl;

            Drive::init();
            std::cout << "Drive Initialized" << std::endl;
            BallIntake::init();
            std::cout << "Ball Intake Initialized" << std::endl;
            Cap::init();
            std::cout << "Cap Initialized" << std::endl;
            Shooter::init();
            std::cout << "Shooter Initialized" << std::endl;

            init_auto();
        }
        catch(std::exception& e){
            std::cerr << "Init error" << std::endl;
            std::cerr << e.what() << std::endl;

            throw std::runtime_error{"Init error"};
        }
        std::cout << "Initialization Complete" << std::endl;
    }

    void competition_init() {

    }
    void auto_robot() {
        while(true){
            robot2_auto_subsystem->updateInputs();
            robot2_auto_subsystem->updateStates();
            robot2_auto_subsystem->updateActions();
        }
    }

    void op_control(){
        while(true){
            std::string line1 = "Vel: " + std::to_string(
                    Shooter::flywheel_velocity->get_actual_velocity());//std::to_string(Cap::wrist_pid_action->get_target());
            std::string line2 = "E: " + std::to_string(Cap::elbow_encoder->get_position());
            std::string line3 = Cap::cap_state_machine->get_current_state()->get_name();
            std::string other = "W: " + std::to_string(Cap::wrist_encoder->get_position());

            while(line3.length() < 15){
                line3 += " ";
            }

            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 0, 0, line1.c_str());
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 1, 0, line2.c_str());
            pros::c::controller_set_text(pros::E_CONTROLLER_MASTER, 2, 0, other.c_str());

            Cap::cap_subsystem->updateInputs();
            Drive::drive_subsystem->updateInputs();
            BallIntake::ball_intake_subsystem->updateInputs();
            Shooter::shooter_subsystem->updateInputs();

            Cap::cap_subsystem->updateStates();
            Drive::drive_subsystem->updateStates();
            BallIntake::ball_intake_subsystem->updateStates();
            Shooter::shooter_subsystem->updateStates();

            Cap::cap_subsystem->updateActions();
            Drive::drive_subsystem->updateActions();
            BallIntake::ball_intake_subsystem->updateActions();
            Shooter::shooter_subsystem->updateActions();

            // serial_manager->enqueue_write (ODROID_ID, 0, serial_manager->odroid_table.read(0));
            // serial_manager->enqueue_write (ODROID_ID, 1, serial_manager->odroid_table.read(1));
            // serial_manager->enqueue_write (ODROID_ID, 2, serial_manager->odroid_table.read(2));
            // serial_manager->enqueue_write (ODROID_ID, 3, serial_manager->odroid_table.read(3));

            // serial_manager->update();
            // pros::delay(10);

//            if(pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_A)){
//                Cap::arm_encoder->tare_position();
//            }
//            if(pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_B)){
//                Cap::elbow_encoder->tare_position();
//            }

            if(pros::c::controller_get_digital(pros::E_CONTROLLER_MASTER, pros::E_CONTROLLER_DIGITAL_LEFT)){
                break;
            }

            //serial_manager->update();
        }
        for(uint8_t x = 1; x < 21; x++){
            pros::c::motor_move_voltage(x, 0);
        }
    }

    void disabled_robot() {

    }

    void destroy() {
        destroy_serial_manager();
        BaseReadable::destroy_battery();
        BaseReadable::destroy_competition();
        //BaseReadable::destroy_controllers();
        destroy_ports_list();

        Drive::destroy();
        //Cap::destroy();
        //BallIntake::destroy();
        Shooter::destroy();

    }
    void restart() {
        destroy();
        init_robot();
    }
}

#pragma clang diagnostic pop
