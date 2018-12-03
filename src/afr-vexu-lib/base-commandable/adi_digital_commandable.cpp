#include "afr-vexu-lib/base-commandable/adi_digital_commandable.h"

namespace AFR::VexU::BaseCommandable {
    error_t adi_digital_commandable::set_value_private(const std::any &value) {
        AFR_PROS_INTERNAL_CALL(adi_digital_out.set_value(std::any_cast<bool>(value)), PROS_ERR);
        return SUCCESS;
    }

    error_t adi_digital_commandable::check_value_private(const std::any &value) {
        if (std::type_index(value.type()) == std::type_index(typeid(bool))) {
            auto real_value = std::any_cast<bool>(value);
            if (real_value != false && real_value != true) {
                return INVALID_VALUE;
            }
            return SUCCESS;
        }
        return INVALID_TYPE;
    }

    adi_digital_commandable::adi_digital_commandable(const uint8_t &port, error_t *result) : commandable(0, result),
                                                                                             adi_digital_out(port) {}

    error_t adi_digital_commandable::get_type(std::type_index &result) const {
        result = typeid(bool);
        return SUCCESS;
    }
}
