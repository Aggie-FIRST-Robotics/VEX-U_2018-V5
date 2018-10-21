#ifndef VEX_U_2018_V5_ORDERED_READABLE_H
#define VEX_U_2018_V5_ORDERED_READABLE_H

#include "readable.h"

namespace AFR::VexU{
    typedef int order_t;

    class ordered_readable{
        order_t order_;
        readable_no_temp& input_;

    public:
        ordered_readable(const order_t& order, readable_no_temp& input);

        order_t get_order() const;
        readable_no_temp& get_input();

        void update();
    };
}

#endif //VEX_U_2018_V5_ORDERED_READABLE_H
