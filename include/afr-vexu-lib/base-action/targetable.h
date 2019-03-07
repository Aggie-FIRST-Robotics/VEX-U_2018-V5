#ifndef VEX_U_2018_V5_TARGETABLE_H
#define VEX_U_2018_V5_TARGETABLE_H

#include <functional>
#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseAction{

    template<typename Read_T>
    class targetable : public nameable {
        
        Read_T initial_value_;
    public:
        targetable(Read_T initial_value, const std::string& name)
                : nameable(name), initial_value_(initial_value) {}

        virtual bool is_in_range(Read_T tolerance) = 0;
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
