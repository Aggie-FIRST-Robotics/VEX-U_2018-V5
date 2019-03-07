#ifndef VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H
#define VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H

#include "main.h"

#include "afr-lib/commandable.h"

namespace AFR::VexU::BaseCommandable{
    class adi_analog_commandable : public commandable{
        port_t port_;

        void set_value_private(const std::any& value) override;
        void check_value_private(const std::any& value) override;

    public:
        explicit adi_analog_commandable(port_t port, const std::string& name);

        std::type_index get_type() const override;
    };
}

#endif //VEX_U_2018_V5_ADI_ANALOG_COMMANDABLE_H
