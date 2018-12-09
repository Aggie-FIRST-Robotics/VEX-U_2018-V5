#ifndef VEX_U_2018_V5_DATA_H
#define VEX_U_2018_V5_DATA_H

#include "main.h"

namespace AFR::VexU::Emulator{
    struct port_data{
        virtual ~port_data() = default;
    };

    struct motor_data : port_data{
        pros::motor_gearset_e_t gearset = pros::E_MOTOR_GEARSET_18;
        bool reversed = false;
        pros::motor_encoder_units_e_t encoder_units = pros::E_MOTOR_ENCODER_DEGREES;
        pros::motor_brake_mode_e_t brake_mode = pros::E_MOTOR_BRAKE_COAST;
        int16_t target_voltage = 0;
        int16_t actual_voltage = 0;
        int32_t voltage_limit = 12000;
        double velocity = 0.0;
        int32_t current_draw = 0;
        int32_t current_limit = 2500;
        uint32_t faults = pros::E_MOTOR_FAULT_NO_FAULTS;
        uint32_t flags = pros::E_MOTOR_FLAGS_NONE;
        double position = 0;
        double temperature = 20.0;
    };

    enum port_type{
        MOTOR,

    };
}

#endif //VEX_U_2018_V5_DATA_H
