#include "afr-vexu-lib/base-readable/adi_encoder_readable.h"

namespace AFR::VexU::BaseReadable{
    error_t adi_encoder_readable::update_private(const double& delta_seconds){
        int32_t temp_val = adi_encoder.get_value();
        AFR_PROS_INTERNAL_CALL(temp_val, PROS_ERR);
        readable::value = temp_val;
        return SUCCESS;
    }

    adi_encoder_readable::adi_encoder_readable(const uint8_t& port_top, const uint8_t& port_bottom,
                                               const bool& reversed, const double& scaling_factor,
                                               const AFR::VexU::scheduled_update_t& update_period,
                                               AFR::VexU::error_t* result) : readable(update_period, 0, result),
                                                                             adi_encoder(port_top, port_bottom,
                                                                                         reversed),
                                                                             scaling_factor(scaling_factor){
    }

    error_t adi_encoder_readable::reset(){
        AFR_PROS_INTERNAL_CALL(adi_encoder.reset(), PROS_ERR);
        return SUCCESS;
    }

    error_t adi_encoder_readable::set_scalling_factor(const double& scaling_factor){
        this->scaling_factor = scaling_factor;
        return SUCCESS;
    }

    error_t adi_encoder_readable::get_scaled_value(double& result){
        result = std::any_cast<int32_t>(readable::value) * scaling_factor;
        return SUCCESS;
    }
}
