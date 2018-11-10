#ifndef VEX_U_2018_V5_READABLE_H
#define VEX_U_2018_V5_READABLE_H

#include <any>

#include "scheduled.h"

namespace AFR::VexU{
    class readable : public scheduled{
    protected:
        std::any value;

    public:
        readable(const scheduled_update_t& update_period, const std::any& initial_value, error_t* result = nullptr);

        error_t get_value(std::any& result) const;
    };
}

#endif //VEX_U_2018_V5_READABLE_H
