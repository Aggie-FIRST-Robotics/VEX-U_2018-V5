#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include "scheduled.h"
#include "commandable.h"

namespace AFR::VexU{
    template<typename DataType>
    class action : public scheduled{
    protected:
        commandable<DataType>* commandable_;

    public:
        explicit action(commandable<DataType>* commandable);
    };

    template<typename DataType>
    action<DataType>::action(commandable<DataType>* commandable) : commandable_(commandable){}
}

#endif //VEX_U_2018_V5_ACTION_H
