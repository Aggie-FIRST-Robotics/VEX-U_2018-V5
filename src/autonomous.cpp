#include "main.h"
#include "afr-vexu-lib/defines.h"

#ifndef ROBOT_2
#include "robot/cap/cap.h"
#include "robot/robot.h"
#else

#include "robot2/cap/cap.h"
#include "robot2/robot.h"
#endif

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(){
#ifndef ROBOT_2
    using namespace AFR::VexU::Robot;

    const bool is_red = false;

    pros::c::motor_set_gearing(RIGHT_RAIL_MOTOR_A_PORT, RIGHT_RAIL_MOTOR_A_GEARSET);
    pros::c::motor_set_gearing(RIGHT_RAIL_MOTOR_B_PORT, RIGHT_RAIL_MOTOR_B_GEARSET);
    pros::c::motor_set_gearing(LEFT_RAIL_MOTOR_A_PORT, LEFT_RAIL_MOTOR_A_GEARSET);
    pros::c::motor_set_gearing(LEFT_RAIL_MOTOR_B_PORT, LEFT_RAIL_MOTOR_A_GEARSET);

    pros::c::motor_set_encoder_units(RIGHT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(RIGHT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(LEFT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(LEFT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);

    pros::c::motor_set_reversed(RIGHT_RAIL_MOTOR_A_PORT, false);
    pros::c::motor_set_reversed(RIGHT_RAIL_MOTOR_B_PORT, false);
    pros::c::motor_set_reversed(LEFT_RAIL_MOTOR_A_PORT, true);
    pros::c::motor_set_reversed(LEFT_RAIL_MOTOR_B_PORT, true);

    //Back up
    double howMany = 2;
    int32_t rpm = 200;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

    pros::delay(2000);

    howMany = -2.0;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, !is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, !is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, !is_red ? howMany : -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, !is_red ? howMany : -howMany, rpm);

    pros::delay(2000);

    howMany = 4.35;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

    pros::delay(2000);

    howMany = -2.0;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, !is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, !is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, !is_red ? howMany : -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, !is_red ? howMany : -howMany, rpm);

    pros::delay(2000);

    Cap::arm_encoder->tare_position();
    Cap::arm_pid_action->set_target(Cap::ARM_FLIP_TARGET);
    howMany = -10;
    rpm = 1 << 30;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);
    while(true){
        Cap::arm_pid_action->update();
    }
#else
    using namespace AFR::VexU::Robot2;

    const bool is_red = true;

    pros::c::motor_set_gearing(RIGHT_RAIL_MOTOR_A_PORT, RIGHT_RAIL_MOTOR_A_GEARSET);
    pros::c::motor_set_gearing(RIGHT_RAIL_MOTOR_B_PORT, RIGHT_RAIL_MOTOR_B_GEARSET);
    pros::c::motor_set_gearing(LEFT_RAIL_MOTOR_A_PORT, LEFT_RAIL_MOTOR_A_GEARSET);
    pros::c::motor_set_gearing(LEFT_RAIL_MOTOR_B_PORT, LEFT_RAIL_MOTOR_A_GEARSET);

    pros::c::motor_set_encoder_units(RIGHT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(RIGHT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(LEFT_RAIL_MOTOR_A_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);
    pros::c::motor_set_encoder_units(LEFT_RAIL_MOTOR_B_PORT, pros::E_MOTOR_ENCODER_ROTATIONS);

    pros::c::motor_set_reversed(RIGHT_RAIL_MOTOR_A_PORT, false);
    pros::c::motor_set_reversed(RIGHT_RAIL_MOTOR_B_PORT, false);
    pros::c::motor_set_reversed(LEFT_RAIL_MOTOR_A_PORT, true);
    pros::c::motor_set_reversed(LEFT_RAIL_MOTOR_B_PORT, true);

    pros::delay(1000);

    while(!Cap::arm_zero_action->is_zeroed() || !Cap::elbow_zero_action->is_zeroed() ||
          !Cap::wrist_zero_action->is_zeroed()){
        Cap::arm_zero_action->update();
        Cap::elbow_zero_action->update();
        Cap::wrist_zero_action->update();
    }

    double howMany = 6;
    int32_t rpm = 150;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

    Cap::arm_pid_action->set_target(Cap::ANGLE_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::ANGLE_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 12000);
    uint32_t wait = pros::millis() + 3000;
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
    }

    howMany = -4;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 3000);
    wait = pros::millis() + 3000;
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
    }

    howMany = 2;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, is_red ? howMany : -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, is_red ? howMany : -howMany, rpm);

    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 3000);
    wait = pros::millis() + 3000;
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
    }

    howMany = 2.15;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 3000);
    wait = pros::millis() + 3000;
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
    }

    howMany = 2;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, is_red ? howMany : -howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, is_red ? howMany : -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, is_red ? -howMany : howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, is_red ? -howMany : howMany, rpm);

    Cap::arm_pid_action->set_target(Cap::FLIP_HIGH_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::FLIP_HIGH_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 3000);
    wait = pros::millis() + 3000;
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
    Cap::wrist_flip->flip();
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }

    int16_t pow = -3000;
    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_A_PORT, pow);
    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_B_PORT, pow);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_A_PORT, pow);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_B_PORT, pow);

    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 3000);
    wait = pros::millis() + 4000;
    while(pros::millis() < wait){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }

    pow = -2000;
    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_A_PORT, pow);
    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_B_PORT, pow);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_A_PORT, pow);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_B_PORT, pow);

    Cap::arm_pid_action->set_target(Cap::SCORE_PRIME_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::SCORE_PRIME_ELBOW_TARGET);
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
    Cap::arm_pid_action->set_target(Cap::SCORE_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::SCORE_ELBOW_TARGET);
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, -12000);
    Cap::arm_pid_action->set_target(Cap::PULL_BACK_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::PULL_BACK_ELBOW_TARGET);
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
    pros::c::motor_move_voltage(INTAKE_MOTOR_PORT, 0);
    Cap::arm_pid_action->set_target(Cap::HOLD_ARM_TARGET);
    Cap::elbow_pid_action->set_target(Cap::HOLD_ELBOW_TARGET);
    while(!Cap::arm_pid_action->is_in_range(50) || !Cap::elbow_pid_action->is_in_range(50) || !Cap::wrist_pid_action){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }

    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_A_PORT, 0);
    pros::c::motor_move_voltage(RIGHT_RAIL_MOTOR_B_PORT, 0);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_A_PORT, 0);
    pros::c::motor_move_voltage(LEFT_RAIL_MOTOR_B_PORT, 0);

    while(true){
        Cap::arm_pid_action->update();
        Cap::elbow_pid_action->update();
        Cap::wrist_pid_action->update();
    }
#endif
}
