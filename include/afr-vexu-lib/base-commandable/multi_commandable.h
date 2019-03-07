#ifndef VEX_U_2018_V5_MULTI_COMMANDABLE_H
#define VEX_U_2018_V5_MULTI_COMMANDABLE_H

#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{
    template<typename T>
    class multi_commandable : public commandable{
        std::vector<commandable*> commandables_;

        void set_value_private(const std::any& value) override{
            for(auto command : commandables_){
                command->set_value(value);
            }
        }

        void check_value_private(const std::any& value) override{}

    public:
        multi_commandable(const std::any& initial_value, const std::string& name) :
                commandable(initial_value, name), commandables_(){}

        void add_commandable(commandable* command){
            commandables_.push_back(command);
        }

        std::type_index get_type() const override{
            return typeid(T);
        }
    };
}

#endif //VEX_U_2018_V5_MULTI_COMMANDABLE_H
