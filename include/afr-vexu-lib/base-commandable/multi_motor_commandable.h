#ifndef VEX_U_2018_V5_MULTI_MOTOR_COMMANDABLE_H
#define VEX_U_2018_V5_MULTI_MOTOR_COMMANDABLE_H

#include <vector>

#include "afr-vexu-lib/base-commandable/motor_commandable.h"

namespace AFR::VexU::BaseCommandable{
    class multi_motor_commandable : public commandable{
        std::vector<motor_commandable*> motors_;

        void set_value_private(const std::any& value) override{
            for(auto motor : motors_){
                motor->set_value(value);
            }
        }

        void check_value_private(const std::any& value) override{}

    public:
        explicit multi_motor_commandable(const std::string& name) : commandable(int16_t(0), name), motors_(){}

        void add_motor(motor_commandable* motor){
            motors_.push_back(motor);
        }

        std::type_index get_type() const override{
            return typeid(int16_t);
        }
    };
}

#endif //VEX_U_2018_V5_MULTI_MOTOR_COMMANDABLE_H
