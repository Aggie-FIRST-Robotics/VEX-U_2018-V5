#ifndef VEX_U_2018_V51_ADI_ANALOG_READABLE_H
#define VEX_U_2018_V51_ADI_ANALOG_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents an AnalogInput object such as a gyroscope or another sensor
    */
    class adi_analog_readable : public readable {
    private:
        /**
        * Creates a pros ADIAnalogIn variable that will be wrapped
        */
        port_t port_;

        /**
        * Overridden to  be whatever happens when update is called following the wait period
        * @param delta_seconds the amount of seconds that have actually passed, however this is not used in this class
        * @return error_t value if error encountered
        */

        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates an adi_analog_readable
         * @param port the port of the object
         * @param update_period passed to readable
         * @param initial_value passed to readable
         * @param name error_t passed to readable
         */
        adi_analog_readable(port_t port, const std::string& name);

        std::any get_value() override;
    };

}
#endif //VEX_U_2018_V51_ADI_ANALOG_READABLE_H
