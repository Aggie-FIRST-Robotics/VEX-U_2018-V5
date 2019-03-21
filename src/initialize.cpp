#include "main.h"
#include "afr-lib/defines.h"


#include "fuego/fuego.h"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    AFR::VexU::Fuego::init_robot();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(){
    if(AFR::VexU::Fuego::before_op_control){ /////Run autonomous exit routine
        AFR::VexU::Fuego::before_op_control = false;

    }
    else{ /////Run op control exit routine

    }
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
