#ifndef VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
#define VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H

#include "main.h"

#include "afr-vexu-lib/commandable.h"

namespace AFR::VexU::BaseCommandable {
    class adi_digital_commandable : public commandable {
        pros::ADIDigitalOut adi_digital_out;

        void set_value_private(const std::any& value) override;

        void check_value_private(const std::any& value) override;

    public:
        explicit adi_digital_commandable(const uint8_t &port, error_t *result = nullptr);

        std::type_index get_type() const override;
    };
}

#endif //VEX_U_2018_V5_ADI_DIGITAL_COMMANDABLE_H
