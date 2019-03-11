#include "afr-vexu-lib/base-readable/adi_encoder_readable.h"

namespace AFR::VexU::BaseReadable{
    adi_encoder_readable::adi_encoder_readable(port_t port_top, port_t port_bottom, bool reversed,
                                               double scaling_factor, const std::string& name)
            : nameable(name), encoder_(pros::c::adi_encoder_init(port_top, port_bottom, reversed)),
              scaling_factor_(scaling_factor){
        claim_adi(port_top, name + "_top");
        claim_adi(port_bottom, name + "_bottom");
    }

    void adi_encoder_readable::reset(){
        if(pros::c::adi_encoder_reset(encoder_) == PROS_ERR){
            throw std::runtime_error{"Error resetting encoder " + std::to_string(encoder_)};
        }
    }

    void adi_encoder_readable::set_scalling_factor(const double& scaling_factor){
        this->scaling_factor_ = scaling_factor;
    }

    double adi_encoder_readable::get_scaled_position(){
        return get_position() * scaling_factor_;
    }

    int32_t adi_encoder_readable::get_position(){
        return pros::c::adi_encoder_get(encoder_);
    }
}
