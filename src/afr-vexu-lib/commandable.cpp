#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU{
//    AFR::VexU::invalid_value_error::invalid_value_error() : runtime_error("Invalid value!"){}

    commandable::commandable(const std::any& initial_value, const std::string& name)
            : nameable(name), current_value_(initial_value){
        std::cout << "COMMANDABLE!" << std::endl;
        std::cout << "END!" << std::endl;
    }

    std::any commandable::get_current_value() const{
        return current_value_;
    }

    void commandable::set_value(const std::any& value){
        std::cout << "FUN TIMES" << std::endl;
        std::type_index type{get_type()};
        std::cout << "asd" << std::endl;
        get_type();
        std::cout << "yea" << std::endl;
        if(std::type_index{value.type()} != type){
            throw std::runtime_error{
                    std::string{"Bad type given to commandable "} + get_name() + ": " + value.type().name() + "!"};
        }
        std::cout << "Swwewew" << std::endl;
        check_value_private(value);
        current_value_ = value;
        set_value_private(value);
        std::cout << "Fim" << std::endl;
    }

//    AFR::VexU::commandable& AFR::VexU::commandable::operator=(const std::any& value){
//        set_value(value);
//        return *this;
//    }
}
