#ifndef VEX_U_2018_V5_DIGITAL_READABLE_H
#define VEX_U_2018_V5_DIGITAL_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable{
    /**
     * Represents any digital sensor or readable input
     */
     class adi_digital_readable : public virtual nameable {
         port_t port_;

     public:
         /**
          * Creates a basic digital readable
          * @param update_period the update period for the readable
          * @param port v5 port to use
          * @param name error_t value if error encountered
          */
         adi_digital_readable(port_t port, const std::string& name);

         bool is_pressed();
     };
}


#endif //VEX_U_2018_V5_DIGITAL_READABLE_H
