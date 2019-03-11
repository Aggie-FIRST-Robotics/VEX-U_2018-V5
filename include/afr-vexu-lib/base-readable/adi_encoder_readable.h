#ifndef VEX_U_2018_V5_ADI_ENCODER_READABLE_H
#define VEX_U_2018_V5_ADI_ENCODER_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable{
    class adi_encoder_readable : public virtual nameable{
        pros::c::adi_encoder_t encoder_;
        double scaling_factor_;

    public:
        adi_encoder_readable(port_t port_top, port_t port_bottom, bool reversed, double scaling_factor,
                             const std::string& name);

        void reset();
        void set_scalling_factor(const double& scaling_factor);
        double get_scaled_position();
        int32_t get_position();
    };
}

#endif //VEX_U_2018_V5_ADI_ENCODER_READABLE_H
