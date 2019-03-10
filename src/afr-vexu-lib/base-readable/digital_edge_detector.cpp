#include "afr-vexu-lib/base-readable/digital_edge_detector.h"

namespace AFR::VexU::BaseReadable{
    digital_edge_detector::digital_edge_detector(std::function<bool()> bool_function, const std::string& name)
            : nameable(name), bool_function_(bool_function){}

    void digital_edge_detector::set_bool_function(std::function<bool> bool_function){
        bool_function_ = bool_function;
    }

    bool digital_edge_detector::is_rising_edge(){
        bool bool_val = bool_function_();
        bool rising_edge = bool_val && !last_read_;
        last_read_ = bool_val;
        return rising_edge;
    }
    
    bool digital_edge_detector::is_falling_edge(){
        bool bool_val = bool_function_();
        bool falling_edge = ~bool_val && last_read_;
        last_read_ = bool_val;
        return falling_edge;
    }    
}
