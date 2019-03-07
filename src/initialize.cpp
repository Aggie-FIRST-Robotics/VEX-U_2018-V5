#include "main.h"
#include "afr-lib/defines.h"

#ifdef ROBOT_2

#include "robot2/robot.h"

#else
#include "robot/robot.h"
#endif


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
#ifndef ROBOT_2
    AFR::VexU::Robot::init_robot();
#else
    AFR::VexU::Robot2::init_robot();
#endif
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(){
//	AFR::VexU::Robot::disabled_robot();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(){
//	AFR::VexU::Robot::competition_init();
}
