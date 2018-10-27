#ifndef VEX_U_2018_V5_READABLE_H
#define VEX_U_2018_V5_READABLE_H

#include "scheduled.h"
#include <any>

namespace AFR::VexU{
    class readable : public scheduled{
    protected:
        std::any value;

    public:
        readable(const unsigned int& update_period_ms, const std::any& initial_value);

        std::any get_value() const;
    };
}

#endif //VEX_U_2018_V5_READABLE_H
