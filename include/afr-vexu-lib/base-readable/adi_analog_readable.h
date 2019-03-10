#ifndef VEX_U_2018_V51_ADI_ANALOG_READABLE_H
#define VEX_U_2018_V51_ADI_ANALOG_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents an AnalogInput object such as a gyroscope or another sensor
    */
    class adi_analog_readable : public virtual nameable {
    private:
        /**
        * Creates a pros ADIAnalogIn variable that will be wrapped
        */
        port_t port_;

    public:
        /**
         * Creates an adi_analog_readable
         * @param port the port of the object
         * @param update_period passed to readable
         * @param initial_value passed to readable
         * @param name error_t passed to readable
         */
        adi_analog_readable(port_t port, const std::string& name);

        int32_t get_analog_value();
    };

}
#endif //VEX_U_2018_V51_ADI_ANALOG_READABLE_H
