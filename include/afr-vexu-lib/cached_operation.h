#ifndef VEX_U_2018_V5_CACHED_OPERATION_H
#define VEX_U_2018_V5_CACHED_OPERATION_H

#include "operation.h"
#include "scheduled.h"

namespace AFR::VexU{
    /**
     * Represents an operation that is calculated through algorithmic logic on a schedule
     */
    template <class T>
    class cached_operation : public scheduled, public operation <T>{
    protected:
        T cached_value; //The last read value of the operation

    public:
        /**
         * Creates a cached operation
         * @param update_period passed to scheduled
         * @param initial_value the initial value of the operation
         * @param name the name of the operation
         * @param result error_t value if error encountered
         */
        cached_operation(scheduled_update_t update_period, const T& initial_value, const std::string& name)
                        : scheduled(update_period), nameable(name), cached_value(initial_value) {}

        /**
         * Used to get the value of the operation
         * @return error_t value if error encountered
         */
        T get_value() {
            if(get_update_period() == 0){
                force_update();
            }
            return cached_value;
        }
    };
}

#endif //VEX_U_2018_V5_CACHED_OPERATION_H
