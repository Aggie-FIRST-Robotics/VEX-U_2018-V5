#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU{
//    AFR::VexU::invalid_value_error::invalid_value_error() : runtime_error("Invalid value!"){}

    commandable::commandable(const std::any& initial_value, const std::string& name)
            : nameable(name), current_value_(){
        set_value(initial_value);
    }

    std::any commandable::get_current_value() const{
        return current_value_;
    }

    void commandable::set_value(const std::any& value){
        std::type_index type{typeid(int)};
        get_type();
        if(std::type_index{value.type()} != type){
            throw std::runtime_error("Bad type given to commandable!");
        }
        check_value_private(value);
        current_value_ = value;
        set_value_private(value);
    }

//    AFR::VexU::commandable& AFR::VexU::commandable::operator=(const std::any& value){
//        set_value(value);
//        return *this;
//    }
}
