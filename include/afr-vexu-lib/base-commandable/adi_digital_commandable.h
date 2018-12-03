#ifndef VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
#define VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H

#include "main.h"

#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU::BaseCommandable {
    class adi_digital_commandable : public commandable {
        pros::ADIDigitalOut adi_digital_out;

        error_t set_value_private(const std::any &value) override;

        error_t check_value_private(const std::any &value) override;

    public:
        explicit adi_digital_commandable(const uint8_t &port, error_t *result = nullptr);

        error_t get_type(std::type_index &result) const override;
    };
}

#endif //VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
