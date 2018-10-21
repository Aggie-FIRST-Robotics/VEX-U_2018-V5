
#include <afr-vexu-lib/ordered_readable.h>

AFR::VexU::ordered_readable::ordered_readable(const AFR::VexU::order_t& order, AFR::VexU::readable_no_temp& input)
        : order_(order), input_(input){}

AFR::VexU::order_t AFR::VexU::ordered_readable::get_order() const{
    return order_;
}

AFR::VexU::readable_no_temp& AFR::VexU::ordered_readable::get_input(){
    return input_;
}

void AFR::VexU::ordered_readable::update(){
    input_.update();
}
