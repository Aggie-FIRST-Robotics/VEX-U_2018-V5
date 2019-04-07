#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include "afr-lib/nameable.h"

namespace AFR::VexU{
    template<typename T>
    class action : public virtual nameable{
        /**
         * Used to generalize retrieval of updated values
         */
    public:
        /**
         * Overridden to return whichever value is needed
         * @return templated value which is needed
         */
        virtual T get_value_to_set() = 0;
    };
}

#endif //VEX_U_2018_V5_ACTION_H
