#ifndef VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
#define VEX_U_2018_V5_ZERO_ENCODER_ACTION_H

#include "afr-vexu-lib/action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::BaseAction{
    template<typename ReadT, typename WriteT>
    class zero_encoder_action : public action{
        BaseReadable::motor_encoder_readable* encoder_ = nullptr;
        readable* readable_;
        bool is_zeroed_;
        WriteT down_val_;
        ReadT target_val_;
        WriteT zero_val_;

        void update_private(const double& delta_seconds) override{
            if(!is_zeroed_){
                if(std::any_cast<ReadT>(readable_->get_value()) == target_val_){
                    is_zeroed_ = true;
                }
                else{
                    commandable_->set_value(down_val_);
                }
            }
            else{
                commandable_->set_value(zero_val_);
            }
        }

    public:
        zero_encoder_action(scheduled_update_t update_period, commandable* commandable, readable* readable,
                            BaseReadable::motor_encoder_readable* encoder, ReadT target_value, WriteT down_val,
                            WriteT zero_val, const std::string& name) :
                action(update_period, commandable, name), encoder_(encoder), readable_(readable), is_zeroed_(false),
                down_val_(down_val), target_val_(target_value), zero_val_(zero_val){}

        void on_state_entry(state* previous_state) override{
            is_zeroed_ = false;
        }
    };
}

#endif //VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
