#ifndef VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H
#define VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    class motor_encoder_readable : public readable{
        pros::Motor motor;
        double velocity;
        double position;
        double scale_factor;

        void update_private(const double& delta_seconds) override;

    public:
        motor_encoder_readable(const std::uint8_t& port, const pros::motor_gearset_e_t& gearset, const bool& reverse,
                               const double& scale_factor, const scheduled_update_t& update_period,
                               error_t* result = nullptr);

        error_t set_scale_factor(const double& scale_factor);
        error_t get_actual_velocity(double& result);
        error_t get_scaled_velocity(double& result);
        error_t get_position(double& result);
        error_t get_scaled_position(double& result);
        error_t tare_position();
        error_t tare_position(const double& position);
        error_t tare_position_scaled(const double& position);

        std::any get_value() const override;
    };
}

#endif //VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H
