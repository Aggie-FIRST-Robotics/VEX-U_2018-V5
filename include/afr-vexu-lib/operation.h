#ifndef VEX_U_2018_V5_OPERATION_H
#define VEX_U_2018_V5_OPERATION_H

#include "nameable.h"

namespace AFR::VexU{
    /**
     * Represents a value that is calculated through algorithmic logic
     */
    template <class T>
    class operation : public nameable{
    public:
        /**
         * Creates a value
         * @param initial_value the initial value of the value
         * @param result error_t value if error encountered
         */
        operation(const std::string& name);

        /**
         * Used to get the value of the value
         * @return error_t value if error encountered
         */
        virtual T get_value() = 0;
    };
}

#endif //VEX_U_2018_V5_OPERATION_H
