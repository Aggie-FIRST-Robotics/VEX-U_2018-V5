#include "afr-vexu-lib/base-readable/adi_encoder_readable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable{
    void adi_encoder_readable::update_private(const double& delta_seconds){}

    adi_encoder_readable::adi_encoder_readable(port_t port_top, port_t port_bottom, bool reversed,
                                               double scaling_factor, const std::string& name)
            : readable(0, nullptr, name), encoder_(pros::c::adi_encoder_init(port_top, port_bottom, reversed)),
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

    double adi_encoder_readable::get_scaled_value(){
        return std::any_cast<int32_t>(get_value()) * scaling_factor_;
    }

    std::any adi_encoder_readable::get_value(){
        return pros::c::adi_encoder_get(encoder_);
    }
}
