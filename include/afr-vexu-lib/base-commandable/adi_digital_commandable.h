#ifndef VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
#define VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H

#include <main.h>

#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseCommandable {
    class adi_digital_commandable : public commandable<bool>{
        port_t port_;

        void set_value_private(bool value, double delta_seconds);

    public:
        explicit adi_digital_commandable(port_t port, const std::string& name);

    };
}

#endif //VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
