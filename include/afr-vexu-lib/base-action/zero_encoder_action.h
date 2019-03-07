#ifndef VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
#define VEX_U_2018_V5_ZERO_ENCODER_ACTION_H

#include "afr-vexu-lib/base-action/targetable.h"
#include <functional>

namespace AFR::VexU::BaseAction{
    template<typename ReadT, typename TargetReadT, typename WriteT>
    class zero_encoder_action : nameable {
        BaseReadable::motor_encoder_readable* encoder_;
        std::function<ReadT()>* readable_;
        bool is_zeroed_;
        WriteT down_val_;
        ReadT target_val_;
        BaseAction::targetable<TargetReadT>* target_action_;

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
                target_action_->update();
            }
        }

    public:
        zero_encoder_action(const std::function<ReadT()>& readable, BaseReadable::motor_encoder_readable* encoder,
                            ReadT target_value, WriteT down_val, BaseAction::targetable<TargetReadT>* target_action,
                            const std::string& name) :
                nameable(name), encoder_(encoder), readable_(readable), is_zeroed_(false),
                down_val_(down_val), target_val_(target_value), target_action_(target_action){}

        bool is_zeroed(){
            return is_zeroed_;
        }
    };
}

#endif //VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
