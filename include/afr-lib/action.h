#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include "nameable.h"

namespace AFR::VexU{
    template<typename T>
    class action : public virtual nameable{
    public:
        virtual T get_value_to_set() = 0;
    };
}

#endif //VEX_U_2018_V5_ACTION_H
