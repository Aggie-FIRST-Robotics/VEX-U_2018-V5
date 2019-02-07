#include "afr-vexu-lib/base-readable/adi_encoder_readable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable{
    void adi_encoder_readable::update_private(const double& delta_seconds){
        int32_t temp_val = pros::c::adi_encoder_get(encoder_);
        if(temp_val == PROS_ERR){
            throw std::runtime_error{"Bad pros adi encoder value!"};
        }
        readable::value = temp_val;
    }

    adi_encoder_readable::adi_encoder_readable(port_t port_top, port_t port_bottom, bool reversed,
                                               double scaling_factor,
                                               scheduled_update_t update_period, const std::string& name)
            : readable(update_period, static_cast<int32_t>(0), name),
              encoder_(pros::c::adi_encoder_init(port_top, port_bottom, reversed)), scaling_factor_(scaling_factor){
        claim_adi(port_top, name + "_top");
        claim_adi(port_bottom, name + "_bottom");
    }

    void adi_encoder_readable::reset(){
        if(pros::c::adi_encoder_reset(encoder_) == PROS_ERR){
            throw std::runtime_error{"Error reseting encoder " + std::to_string(encoder_)};
        }
    }

    void adi_encoder_readable::set_scalling_factor(const double& scaling_factor){
        this->scaling_factor_ = scaling_factor;
    }

    double adi_encoder_readable::get_scaled_value(){
        return std::any_cast<int32_t>(readable::value) * scaling_factor_;
    }
}
