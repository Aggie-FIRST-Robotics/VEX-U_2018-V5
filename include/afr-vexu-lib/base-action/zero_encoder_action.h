#ifndef VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
#define VEX_U_2018_V5_ZERO_ENCODER_ACTION_H

#include "afr-vexu-lib/action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-action/targetable.h"

namespace AFR::VexU::BaseAction{
    template<typename ReadT, typename TargetReadT, typename WriteT>
    class zero_encoder_action : public action{
        BaseReadable::motor_encoder_readable* encoder_;
        readable* readable_;
        bool is_zeroed_;
        WriteT down_val_;
        ReadT target_val_;
        BaseAction::targetable<TargetReadT>* target_action_;

        void update_private(const double& delta_seconds) override{
            if(!is_zeroed_){
                if(std::any_cast<ReadT>(readable_->get_value()) == target_val_){
                    is_zeroed_ = true;
                    encoder_->tare_position();
                    target_action_->set_target(0);
                }
                else{
                    commandable_->set_value(down_val_);
                }
            }
            else{
                target_action_->update();
            }
        }

    public:
        zero_encoder_action(scheduled_update_t update_period, commandable* commandable, readable* readable,
                            BaseReadable::motor_encoder_readable* encoder, ReadT target_value, WriteT down_val,
                            BaseAction::targetable<TargetReadT>* target_action, const std::string& name) :
                action(update_period, commandable, name), encoder_(encoder), readable_(readable), is_zeroed_(false),
                down_val_(down_val), target_val_(target_value), target_action_(target_action){}

        void on_state_entry(state* previous_state) override{
            is_zeroed_ = false;
        }

        bool is_zeroed(){
            return is_zeroed_;
        }
    };
}

#endif //VEX_U_2018_V5_ZERO_ENCODER_ACTION_H
