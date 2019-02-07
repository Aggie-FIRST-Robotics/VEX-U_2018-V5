#ifndef VEX_U_2018_V5_ACTION_H
#define VEX_U_2018_V5_ACTION_H

#include <any>

#include "scheduled.h"
#include "commandable.h"
#include "nameable.h"

namespace AFR::VexU{
    class state;
    /**
     * Represents a method of control for a single commandable. Will be updated after readables.
     * Should not be more complicated than a PID controller or direct input conversion.
     */
    class action : public scheduled, public nameable{
    protected:
        commandable* commandable_;  ///Reference to the commandable this action commands

    public:
        /**
         * Creates an action
         * @param update_period passed to scheduled
         * @param commandable the commandable this action commands
         * @param result error_t value if error encountered
         */
        explicit action(scheduled_update_t update_period, commandable* commandable, const std::string& name);

        virtual void on_state_entry(state* previous_state);
        virtual void on_state_exit(state* next_state);
    };
}

#endif //VEX_U_2018_V5_ACTION_H
