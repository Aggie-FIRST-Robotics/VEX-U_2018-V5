
#ifndef VEX_U_2018_V51_ADI_ANALOG_READABLE_H
#define VEX_U_2018_V51_ADI_ANALOG_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents an AnalogInput object such as a gyroscope or another sensor
    */
    class adi_analog_readable : public readable {
    private:
        /**
        * Creates a pros ADIAnalogIn variable that will be wrapped
        */
        pros::ADIAnalogIn temp;

        /**
        * Overridden to  be whatever happens when update is called following the wait period
        * @param delta_seconds the amount of seconds that have actually passed, however this is not used in this class
        * @return error_t value if error encountered
        */

        error_t update_private(const double &delta_seconds) override;

    public:
        /**
         * Creates an adi_analog_readable
         * @param port the port of the object
         * @param update_period passed to readable
         * @param initial_value passed to readable
         * @param result error_t passed to readable
         */
        adi_analog_readable(const std::uint8_t &port, const scheduled_update_t &update_period,
                            const std::any &initial_value, error_t *result);

    };

}
#endif //VEX_U_2018_V51_ADI_ANALOG_READABLE_H
