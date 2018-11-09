#include <afr-vexu-lib/commandable.h>

AFR::VexU::invalid_value_error::invalid_value_error() : runtime_error("Invalid value!"){}

AFR::VexU::commandable::commandable(const std::any& initial_value) : current_value_(initial_value){}

std::any AFR::VexU::commandable::get_current_value() const{
    return current_value_;
}

void AFR::VexU::commandable::set_value(const std::any& value){
    if(!check_value_private(value)){
        throw invalid_value_error();
    }
    set_value_private(value);
    current_value_ = value;
}

AFR::VexU::commandable& AFR::VexU::commandable::operator=(const std::any& value){
    set_value(value);
    return *this;
}

