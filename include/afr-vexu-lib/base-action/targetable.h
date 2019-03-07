#ifndef VEX_U_2018_V5_TARGETABLE_H
#define VEX_U_2018_V5_TARGETABLE_H

#include <functional>
#include "cached_operation.h"
#include "defines.h"

namespace AFR::VexU::BaseAction{

    template<typename Read_T>
    class targetable : public commandable<Read_T> {
        
        Read_T initial_value_;
    public:
        targetable(scheduled_update_t update_period, Read_T initial_value,
                   const std::string& name)
                : commandable<Read_T>(update_period, name), initial_value_(initial_value) {}

        virtual bool is_in_range(Read_T tolerance) = 0;
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
