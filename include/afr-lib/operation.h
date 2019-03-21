#ifndef VEX_U_2018_V5_OPERATION_H
#define VEX_U_2018_V5_OPERATION_H

#include <functional>

#include "afr-lib/nameable.h"

namespace AFR::VexU{
    template <class T>
    class operation : public virtual nameable {
        /**
        * Represents a certain operation on the Robot
        */

        std::function<T()> function_;
        
    public:
        /**
        * Creates operation with adjustable operation function and name
        * @param operation_function function that the operation will run
        * @param name to be assigned to the object
        */
        operation(const std::function<T()>& operation_function, const std::string& name)
                : nameable(name), function_(operation_function) {}

        /**
        * sets the operation function
        * @param operation_function function the operation will be set to
        */
        void set_function(const std::function<T()>& operation_function) {
            function_ = operation_function;
        }

        /**
        * returns the function
        */
        std::function<T()>& get_function() {
            return function_;
        }
    };
}
#endif //VEX_U_2018_V5_OPERATION_H