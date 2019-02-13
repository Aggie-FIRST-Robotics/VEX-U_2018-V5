#ifndef VEX_U_2018_V5_READABLE_H
#define VEX_U_2018_V5_READABLE_H

#include <any>

#include "scheduled.h"
#include "nameable.h"

namespace AFR::VexU{
    /**
     * Represents a sensor or other readable value, should be extended
     */
    class readable : public scheduled, public nameable{
    protected:
        std::any value; ///The last read value of the readable

    public:
        /**
         * Creates a readable
         * @param update_period passed to scheduled
         * @param initial_value the initial value of the readable
         * @param result error_t value if error encountered
         */
        readable(scheduled_update_t update_period, const std::any& initial_value, const std::string& name);

        /**
         * Used to get the value of the readable
         * @param result Returns the value of the sensor
         * @return error_t value if error encountered
         */
        virtual std::any get_value();
    };
}

#endif //VEX_U_2018_V5_READABLE_H
