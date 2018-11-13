#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include <any>

#include "scheduled.h"
#include "commandable.h"

namespace AFR::VexU{
    class action : public scheduled {
    protected:
        commandable& commandable_;  ///Reference to the commandable this action commands

    public:
        /**
         * Creates an action
         * @param update_period the time period to be updated in of type scheduled_update_t
         * @param commandable the commandable this action commands
         * @param result error_t value if error encountered
         */
        explicit action(const scheduled_update_t& update_period, commandable& commandable, error_t* result = nullptr);
    };
}

#endif //VEX_U_2018_V5_ACTION_H
