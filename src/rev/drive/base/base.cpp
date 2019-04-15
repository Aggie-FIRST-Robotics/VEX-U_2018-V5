#include "rev/drive/base/base.h"

namespace AFR::VexU::Rev::Drive::Base{

    BaseCommandable::motor_commandable* left_motor_1 = nullptr;
    BaseCommandable::motor_commandable* left_motor_2 = nullptr;
    BaseCommandable::motor_commandable* left_motor_3 = nullptr;
    BaseCommandable::motor_commandable* right_motor_1 = nullptr;
    BaseCommandable::motor_commandable* right_motor_2 = nullptr;
    BaseCommandable::motor_commandable* right_motor_3 = nullptr;

    BaseReadable::motor_encoder_readable* left_encoder = nullptr;
    BaseReadable::motor_encoder_readable* right_encoder = nullptr;

    void init(){
        //comment

        left_motor_1 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, LEFT_DRIVE_MOTOR_1, DRIVETRAIN_GEARSET,
                 !DIRECTION,DRIVETRAIN_BRAKE_MODE, "left drive motor 1");
        left_motor_2 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, LEFT_DRIVE_MOTOR_2, DRIVETRAIN_GEARSET,
                 DIRECTION,DRIVETRAIN_BRAKE_MODE, "left drive motor 2");
        left_motor_3 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, LEFT_DRIVE_MOTOR_3, DRIVETRAIN_GEARSET,
                 !DIRECTION,DRIVETRAIN_BRAKE_MODE, "left drive motor 3");
        right_motor_1 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, RIGHT_DRIVE_MOTOR_1, DRIVETRAIN_GEARSET,
                 DIRECTION,DRIVETRAIN_BRAKE_MODE, "right drive motor 1");
        right_motor_2 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, RIGHT_DRIVE_MOTOR_2, DRIVETRAIN_GEARSET,
                 !DIRECTION,DRIVETRAIN_BRAKE_MODE, "right drive motor 2");
        right_motor_3 = new BaseCommandable::motor_commandable
                (UPDATE_PERIOD, RIGHT_DRIVE_MOTOR_3, DRIVETRAIN_GEARSET,
                 DIRECTION,DRIVETRAIN_BRAKE_MODE, "right drive motor 3");

        left_encoder = new BaseReadable::motor_encoder_readable
            (LEFT_DRIVE_MOTOR_1, ENCODER_SCALING, "left drive encoder");
        
        right_encoder = new BaseReadable::motor_encoder_readable
            (RIGHT_DRIVE_MOTOR_1, ENCODER_SCALING, "right drive encoder");

    }

    void destroy(){
        delete left_motor_1;
        delete left_motor_2;
        delete left_motor_3;
        delete right_motor_1;
        delete right_motor_2;
        delete right_motor_3;
        delete left_encoder;
        delete right_encoder;
    }
}
