#ifndef VEX_U_2018_V5_ORDERED_INPUT_H
#define VEX_U_2018_V5_ORDERED_INPUT_H

#include <string>

#include "readable.h"

namespace AFR::VexU{
    typedef unsigned int order_t; ///The type of orders, use this typedef in case of changes

    /**
     * Wraps readable to include an order to allow for updating in order
     */
    class ordered_input{
        order_t order;
        readable* input;

    public:
        /**
         * Creates an ordered input/readable
         * @param order the order of this input of type order_t, lower will be updated first
         * @param input the readable this ordered input wraps
         * @param result error_t value if error encountered
         */
        ordered_input(const order_t& order, readable* input, error_t* result = nullptr);

        /**
         * Gets the order
         * @param result Returns the order
         * @return error_t value if error encountered
         */
        error_t get_order(order_t& result) const;
        /**
         * Gets the readable represented by this
         * @param result Returns the readable as a pointer, should be passed a pointer variable
         * @return error_t value if error encountered
         */
        error_t get_input(readable*& result) const;
    };
}

#endif //VEX_U_2018_V5_ORDERED_INPUT_H
