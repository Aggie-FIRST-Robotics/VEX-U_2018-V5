#ifndef VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H
#define VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H

#include <functional>

#include "main.h"
#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable{
    /**
     * Represents an edge detector for any boolean sensor. A new instance must
     * be created for each separate concurrent checker.
     */
     class digital_edge_detector : public virtual nameable {
        bool last_read_;
        std::function<bool()> bool_function_;
     public:
         /**
          * Creates a basic digital readable
          * @param update_period the update period for the readable
          * @param port v5 port to use
          * @param name error_t value if error encountered
          */
        adi_digital_readable(std::function<bool()> bool_function, const std::string& name);
        
        void set_bool_function(std::function<bool> bool_function);
        bool is_rising_edge();
        bool is_falling_edge();
     };
}


#endif //VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H
