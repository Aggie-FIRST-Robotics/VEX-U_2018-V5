#include <afr-vexu-lib/commandable.h>

//AFR::VexU::invalid_value_error::invalid_value_error() : runtime_error("Invalid value!"){}

AFR::VexU::commandable::commandable(const std::any& initial_value, error_t* result) : current_value_(initial_value){
    if(result != nullptr){
        *result = SUCCESS;
    }
}

AFR::VexU::error_t AFR::VexU::commandable::get_current_value(std::any& result) const{
    result = current_value_;
    return SUCCESS;
}

AFR::VexU::error_t AFR::VexU::commandable::set_value(const std::any& value){
    bool is_good_value = false;
    check_value_private(value, is_good_value);
    if(!is_good_value){
        return INVALID_VALUE;
    }
    current_value_ = value;
    return set_value_private(value);
}

//AFR::VexU::commandable& AFR::VexU::commandable::operator=(const std::any& value){
//    set_value(value);
//    return *this;
//}

