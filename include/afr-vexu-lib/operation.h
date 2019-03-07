#ifndef VEX_U_2018_V5_OPERATION_H
#define VEX_U_2018_V5_OPERATION_H

#include "nameable.h"

namespace AFR::VexU{
    /**
     * Represents an operation that is calculated through algorithmic logic
     */
    template <class T>
    class operation : public virtual nameable{
    public:
        /**
         * Creates an operation
         * @param name the name of the operation
         * @param result error_t value if error encountered
         */
        operation(const std::string& name) : nameable(name) {}

        /**
         * Used to get the value of the operation
         * @return error_t value if error encountered
         */
        virtual T get_value() = 0;
    };
}

#endif //VEX_U_2018_V5_OPERATION_H
