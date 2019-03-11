#ifndef VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H
#define VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H

#include "main.h"
#include "afr-lib/commandable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU::BaseCommandable{
    class adi_analog_commandable : public commandable<int32_t>{
        port_t port_;

        void set_value_private(int32_t value, double delta_seconds);

    public:
        explicit adi_analog_commandable(const scheduled_update_t period, port_t port, const std::string& name);
    };
}

#endif //VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H
