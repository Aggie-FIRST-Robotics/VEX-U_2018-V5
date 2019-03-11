//#ifndef VEX_U_2018_V5_WRIST_FLIP_ACTION_H
//#define VEX_U_2018_V5_WRIST_FLIP_ACTION_H
//
//namespace AFR::VexU::Fuego::Cap{
//    class wrist_flip_action : public action{
//        BaseAction::targetable<double>* wrist_pid_action_;
//        BaseReadable::controller_digital_readable* flip_button_;
//        double flip_target_;
//        bool is_at_start_;
//
//        void update_private(const double& delta_seconds) override{
//        }
//
//    public:
//        wrist_flip_action(scheduled_update_t update_period, BaseAction::targetable<double>* wrist_pid_action,
//                          BaseReadable::controller_digital_readable* flip_button, double flip_target,
//                          const std::string& name) :
//                action(update_period, nullptr, name), wrist_pid_action_(wrist_pid_action), flip_button_(flip_button),
//                flip_target_(flip_target), is_at_start_(true){
//            wrist_pid_action->set_target(0);
//        }
//
//        void reset(){
//            is_at_start_ = true;
//            wrist_pid_action_->set_target(0);
//        }
//
//        void flip(){
//            if(is_at_start_){
//                is_at_start_ = false;
//                wrist_pid_action_->set_target(flip_target_);
//            }
//            else{
//                is_at_start_ = true;
//                wrist_pid_action_->set_target(0);
//            }
//        }
//    };
//}
//
//#endif //VEX_U_2018_V5_WRIST_FLIP_ACTION_H
