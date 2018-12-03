#ifndef VEX_U_2018_V5_ADI_ENCODER_READABLE_H
#define VEX_U_2018_V5_ADI_ENCODER_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    class adi_encoder_readable : public readable{
        pros::ADIEncoder adi_encoder;
        double scaling_factor;

        error_t update_private(const double& delta_seconds) override;

    public:
        adi_encoder_readable(const uint8_t& port_top, const uint8_t& port_bottom, const bool& reversed,
                             const double& scaling_factor,
                             const scheduled_update_t& update_period, error_t* result = nullptr);
        error_t reset();
        error_t set_scalling_factor(const double& scaling_factor);
        error_t get_scaled_value(double& result);
    };
}

#endif //VEX_U_2018_V5_ADI_ENCODER_READABLE_H
