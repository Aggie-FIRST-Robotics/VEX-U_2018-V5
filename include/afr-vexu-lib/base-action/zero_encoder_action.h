#ifndef VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
#define VEX_U_2018_V5_ZERO_ENCODER_ACTION_H

#include "afr-vexu-lib/base-action/targetable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::BaseAction{
    template<typename ReadT, typename WriteT>
    class zero_encoder_action {
        BaseReadable::motor_encoder_readable* encoder_;
        std::function<ReadT()> readable_;
        WriteT down_val_;
        WriteT zero_val_;
        ReadT target_val_;

    public:

        zero_encoder_action(const std::function<ReadT()>& readable, BaseReadable::motor_encoder_readable* encoder,
                            ReadT target_value, WriteT down_val, WriteT zero_val) :
                            encoder_(encoder), readable_(readable), down_val_(down_val), zero_val_(zero_val), target_val_(target_value) {}

        bool is_zeroed(){
            return readable_() == target_val_;
        }

        WriteT zero_value() {
            if(is_zeroed()){
                encoder_->tare_position();
                return zero_val_;
            }
            else{
                return down_val_;
            }
        }

    };
}

#endif //VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
