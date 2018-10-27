#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include <any>

#include "scheduled.h"
#include "commandable.h"

namespace AFR::VexU{
    class action : public scheduled {
    protected:
        commandable *commandable_;

    public:
        explicit action(const unsigned int &update_period_ms, commandable *commandable);
    };
}

#endif //VEX_U_2018_V5_ACTION_H
