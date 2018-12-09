#ifndef VEX_U_2018_V5_DIGITAL_READABLE_H
#define VEX_U_2018_V5_DIGITAL_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    /**
     * Represents any digital sensor or readable input
     */
     class adi_digital_readable : public readable {
        pros::ADIDigitalIn digital;

         /**
          * Overrides scheduled, updates private period
          * @param delta_seconds new update period
          * @return error_t value if error encountered
          */
        error_t update_private(const double& delta_seconds) override;

     public:
         /**
          * Creates a basic digital readable
          * @param update_period the update period for the readable
          * @param port v5 port to use
          * @param result error_t value if error encountered
          */
        adi_digital_readable(const scheduled_update_t& update_period, const std::uint8_t& port,
                             error_t* result = nullptr);
     };
}


#endif //VEX_U_2018_V5_DIGITAL_READABLE_H
