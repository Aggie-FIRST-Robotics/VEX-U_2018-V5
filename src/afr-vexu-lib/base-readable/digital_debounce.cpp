#include "afr-vexu-lib/base-readable/digital_debounce.h"

namespace AFR::VexU::BaseReadable{
    digital_debounce::digital_debounce(std::function<bool()> bool_function, uint8_t threshold, const std::string& name)
            : operation<bool>(bool_function, name), nameable(name), counter_(0), threshold_(threshold) {}

    bool digital_debounce::is_triggered(){
        bool curr_button_val = operation<bool>::get_function()();
        if(operation<bool>::get_function()()){
            counter_++;
        }
        else{
            counter_ = 0;
        }
        return counter_ >= threshold_;
    }

}
