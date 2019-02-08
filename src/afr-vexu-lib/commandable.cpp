#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU{
    commandable::commandable(const std::any& initial_value, const std::string& name)
            : nameable(name), current_value_(initial_value){}

    std::any commandable::get_current_value() const{
        return current_value_;
    }

    void commandable::set_value(const std::any& value){
        std::type_index type{get_type()};
        get_type();
        if(std::type_index{value.type()} != type){
            throw std::runtime_error{
                    std::string{"Bad type given to commandable "} + get_name() + ": " + value.type().name() + "!"};
        }
        check_value_private(value);
        current_value_ = value;
        set_value_private(value);
    }

}
