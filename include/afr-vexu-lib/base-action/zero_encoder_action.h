#ifndef VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
#define VEX_U_2018_V5_ZERO_ENCODER_ACTION_H

#include "afr-vexu-lib/base-action/targetable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"

namespace AFR::VexU::BaseAction{
    template<typename ReadT, typename TargetReadT, typename WriteT>
    class zero_encoder_action : targetable<TargetReadT> {
        BaseReadable::motor_encoder_readable* encoder_;
        std::function<ReadT()>* readable_;
        bool is_zeroed_;
        WriteT down_val_;
        ReadT target_val_;
        BaseAction::targetable<TargetReadT>* target_action_;

        void set_value_private(ReadT value, double delta_seconds){
            target_val_ = value;
        }

        WriteT zero_value() {
            if(!is_zeroed_){
                if(readable_ == target_val_){
                    is_zeroed_ = true;
                    encoder_->tare_position();
                    target_action_->set_target(0);
                }
                else{
                    return down_val_;
                }
            }
            else{
                target_action_->enable();
            }
        }

    public:
        zero_encoder_action(const std::function<ReadT()>& readable, BaseReadable::motor_encoder_readable* encoder,
                            ReadT target_value, WriteT down_val, BaseAction::targetable<TargetReadT>* target_action,
                            const std::string& name) :
                nameable(name), encoder_(encoder), readable_(readable), is_zeroed_(false),
                down_val_(down_val), target_val_(target_value), target_action_(target_action){
            target_action->disable();
        }

        bool is_zeroed(){
            return is_zeroed_;
        }

        bool is_in_range(ReadT tolerance) override{
            return is_zeroed();
        }
    };
}

#endif //VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
