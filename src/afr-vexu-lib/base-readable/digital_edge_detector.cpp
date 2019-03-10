#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::BaseReadable{
    
    digital_edge_detector::digital_edge_detector(std::function<bool()> bool_function, const std::string& name)
            : operation<bool>(bool_function, name), nameable(name){}

    bool digital_edge_detector::is_rising_edge(){
        bool bool_val = operation<bool>::get_function()();
        bool rising_edge = bool_val && !last_read_;
        last_read_ = bool_val;
        return rising_edge;
    }
    
    bool digital_edge_detector::is_falling_edge(){
        bool bool_val = operation<bool>::get_function()();
        bool falling_edge = !bool_val && last_read_;
        last_read_ = bool_val;
        return falling_edge;
    }    
}
