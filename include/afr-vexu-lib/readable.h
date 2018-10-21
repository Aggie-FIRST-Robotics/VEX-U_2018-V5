#ifndef VEX_U_2018_V5_READABLE_H
#define VEX_U_2018_V5_READABLE_H

#include "scheduled.h"

namespace AFR::VexU{
    class readable_no_temp : public scheduled{
    public:
        explicit readable_no_temp(const unsigned int& update_period_ms);
    };

    template<typename DataType>
    class readable : readable_no_temp{
    protected:
        DataType value;

    public:
        readable(const unsigned int& update_period_ms, const DataType& initial_value);

        DataType get_value() const;
    };

    template<typename DataType>
    readable<DataType>::readable(const unsigned int& update_period_ms, const DataType& initial_value)
            : readable_no_temp(update_period_ms), value(initial_value){}

    template<typename DataType>
    DataType readable<DataType>::get_value() const{
        return value;
    }
}

#endif //VEX_U_2018_V5_READABLE_H
