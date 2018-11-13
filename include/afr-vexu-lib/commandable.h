#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <any>
#include <stdexcept>
#include <typeindex>

#include "defines.h"

namespace AFR::VexU{
//    class invalid_value_error : public std::runtime_error{
//    public:
//        invalid_value_error();
//    };

    /**
     * Represents something that can be commanded on the robot, such as a motor or piston actuator.
     * Can be as low level as direct motor control or abstract as a drivebase, as long as it takes a singular value
     */
    class commandable{
    private:
        std::any current_value_;

        /**
         * Sets the value to the checked parameter, no more checking is required
         * @param value checked value to be set
         * @return error_t value if error encountered
         */
        virtual error_t set_value_private(const std::any& value) = 0;
        /**
         * Takes an already type checked value and adds constraints if necessary
         * @param value type checked value to be constrained
         * @return SUCCESS if good value, error_t value otherwise
         */
        virtual error_t check_value_private(const std::any& value) = 0;

    public:
        /**
         *
         * @param initial_value
         * @param result
         */
        explicit commandable(const std::any& initial_value, error_t* result = nullptr);

        /**
         * Returns the expected type for this commandable
         * @param result Output in the form of type_index as typeid cannot be assigned
         * @return error_t value if error encountered
         */
        virtual error_t get_type(std::type_index& result) const = 0;

        /**
         * Returns the current value of the commandable as set by get_current_value. The any returned will be of the
         * same type as get_type
         * @param result the returned value copied
         * @return error_t value if error encountered
         */
        error_t get_current_value(std::any& result) const;

        /**
         * The function used to set the value of this commandable. Will be type checked by default then value checked by check_value_private
         * @param value the value to set, must be of type get_type and pass value check
         * @return error_t value if error encountered
         */
        error_t set_value(const std::any& value);
//        commandable& operator=(const std::any& value);
    };
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
