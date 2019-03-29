#ifndef VEX_U_2018_V5_DIGITAL_DEBOUNCE_H
#define VEX_U_2018_V5_DIGITAL_DEBOUNCE_H

#include "afr-lib/operation.h"

namespace AFR::VexU::BaseReadable{

     class digital_debounce : public operation<bool> {
        uint8_t counter_;
        uint8_t threshold_;

     public:

        digital_debounce(std::function<bool()> bool_function, uint8_t threshold, const std::string& name);
        
        bool is_triggered();
     };
}


#endif //VEX_U_2018_V5_DIGITAL_DEBOUNCE_H
