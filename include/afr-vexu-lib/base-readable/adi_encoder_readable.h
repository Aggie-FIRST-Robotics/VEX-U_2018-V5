#ifndef VEX_U_2018_V5_ADI_ENCODER_READABLE_H
#define VEX_U_2018_V5_ADI_ENCODER_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    class adi_encoder_readable : public readable{
        pros::c::adi_encoder_t encoder_;
        double scaling_factor_;

        void update_private(const double& delta_seconds) override;

    public:
        adi_encoder_readable(port_t port_top, port_t port_bottom, bool reversed,
                             double scaling_factor,
                             scheduled_update_t update_period, const std::string& name);

        void reset();
        void set_scalling_factor(const double& scaling_factor);
        double get_scaled_value();
    };
}

#endif //VEX_U_2018_V5_ADI_ENCODER_READABLE_H
