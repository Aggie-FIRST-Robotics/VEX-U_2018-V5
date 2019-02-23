#include "robot/cap/cap.h"
#include "main.h"

#ifndef ROBOT_2
#include "robot/robot.h"
#else

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

/*    LeftMidDrive.stop(brakeType::hold);  //The motor will now Hold  (resist movement and stay at position)
    LeftRearDrive.stop(brakeType::hold);
    RightMidDrive.stop(brakeType::hold);
    RightRearDrive.stop(brakeType::hold);
*/    pros::delay(2000);

    //Spin Left
    howMany = -2.0;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, -howMany, rpm);

/*    LeftMidDrive.stop(brakeType::hold);  //The motor will now Hold  (resist movement and stay at position)
    LeftRearDrive.stop(brakeType::hold);
    RightMidDrive.stop(brakeType::hold);
    RightRearDrive.stop(brakeType::hold);
*/    pros::delay(2000);

    //Back up
    howMany = 4.35;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);

/*    LeftMidDrive.stop(brakeType::hold);  //The motor will now Hold  (resist movement and stay at position)
    LeftRearDrive.stop(brakeType::hold);
    RightMidDrive.stop(brakeType::hold);
    RightRearDrive.stop(brakeType::hold);
*/    pros::delay(2000);


    //Spin Right
    howMany = -2.0;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, -howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, -howMany, rpm);

/*    LeftMidDrive.stop(brakeType::hold);  //The motor will now Hold  (resist movement and stay at position)
    LeftRearDrive.stop(brakeType::hold);
    RightMidDrive.stop(brakeType::hold);
    RightRearDrive.stop(brakeType::hold);
*/    pros::delay(2000);

    Cap::arm_encoder->tare_position();
    Cap::arm_pid_action->set_target(Cap::ARM_FLIP_TARGET);
    //Park
    howMany = -10;
    rpm = 1 << 30;
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(RIGHT_RAIL_MOTOR_B_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_A_PORT, howMany, rpm);
    pros::c::motor_move_relative(LEFT_RAIL_MOTOR_B_PORT, howMany, rpm);
    while(true){
        Cap::arm_pid_action->update();
    }

/*    LeftMidDrive.stop(brakeType::hold);  //The motor will now Hold  (resist movement and stay at position)
    LeftRearDrive.stop(brakeType::hold);
    RightMidDrive.stop(brakeType::hold);
    RightRearDrive.stop(brakeType::hold);
*/    //pros::delay(2000);
#endif
}
