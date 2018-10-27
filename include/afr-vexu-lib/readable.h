#ifndef VEX_U_2018_V5_READABLE_H
#define VEX_U_2018_V5_READABLE_H

#include "scheduled.h"

namespace AFR::VexU{
    template<typename DataType>
    class readable : public scheduled{
    protected:
        DataType value;

    public:
        readable(const unsigned int& update_period_ms, const DataType& initial_value);

        DataType get_value() const;
    };

    template<typename DataType>
    readable<DataType>::readable(const unsigned int& update_period_ms, const DataType& initial_value)
            : scheduled(update_period_ms), value(initial_value){}

    template<typename DataType>
    DataType readable<DataType>::get_value() const{
        return value;
    }
}

#endif //VEX_U_2018_V5_READABLE_H
