#ifndef VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H
#define VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H

#include "main.h"
#include "afr-lib/operation.h"
#include "controller_readable.h"

namespace AFR::VexU::BaseReadable{
    /**
     * Represents an edge detector for any boolean sensor. A new instance must
     * be created for each separate concurrent checker.
     */
     class digital_edge_detector : public operation<bool> {
        bool last_read_;
        pros::controller_digital_e_t button_;

     public:
         /**
          * Creates a basic digital readable
          * @param update_period the update period for the readable
          * @param port v5 port to use
          * @param name error_t value if error encountered
          */
        digital_edge_detector(std::function<bool()> bool_function, const std::string& name);
        digital_edge_detector(pros::controller_id_e_t id, pros::controller_digital_e_t button, const std::string& name);
        
        bool is_rising_edge();
        bool is_falling_edge();
        void set_last_read(bool val);
     };
}


#endif //VEX_U_2018_V5_DIGITAL_EDGE_DETECTOR_H
