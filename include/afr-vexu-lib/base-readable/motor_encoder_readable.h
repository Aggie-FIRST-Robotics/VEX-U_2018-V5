#ifndef VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H
#define VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"
#include "afr-lib/scheduled.h"

namespace AFR::VexU::BaseReadable{
    class motor_encoder_readable : public virtual nameable {
        port_t port_;
        double scale_factor;
    public:
        motor_encoder_readable(port_t port, double scale_factor, const std::string& name);

        void set_scale_factor(double scale_factor);
        double get_actual_velocity();
        double get_scaled_velocity();
        double get_position();
        double get_scaled_position();
        void tare_position();
        void tare_position(double position);
        void tare_position_scaled(double position);
    };
}

#endif //VEX_U_2018_V5_MOTOR_ENCODER_READABLE_H
