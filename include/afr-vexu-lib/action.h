#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include "scheduled.h"
#include "commandable.h"

namespace AFR::VexU{
    class action_no_temp : public scheduled{
    public:
        explicit action_no_temp(const unsigned int& update_period_ms);
    };

    template<typename DataType>
    class action : public action_no_temp{
    protected:
        commandable<DataType>* commandable_;

    public:
        explicit action(const unsigned int& update_period_ms, commandable<DataType>* commandable);
    };

    template<typename DataType>
    action<DataType>::action(const unsigned int& update_period_ms, commandable <DataType>* commandable)
            : action_no_temp(update_period_ms), commandable_(commandable){}
}

#endif //VEX_U_2018_V5_ACTION_H
