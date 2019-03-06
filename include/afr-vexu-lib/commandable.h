#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <any>
#include <stdexcept>
#include <typeindex>

#include "defines.h"
#include "nameable.h"
#include "operation.h"
#include "scheduled.h"

namespace AFR::VexU{
//    class invalid_value_error : public std::runtime_error{
//    public:
//        invalid_value_error();
//    };

    /**
     * Represents something that can be commanded on the robot, such as a motor or piston actuator.
     * Can be as low level as direct motor control or abstract as a drivebase, as long as it takes a singular value.
     */
    template <class T>
    class commandable : public scheduled {
    private:
        T current_value_;
        std::function<T()> operation_function_;
        bool operation_defined;

        /**
         * Sets the value to the checked parameter, no more checking is required
         * @param value checked value to be set
         * @return error_t value if error encountered
         */
        virtual void set_value_private(T value) = 0;
        
        void update_private(const double& delta_seconds) override {
            if(operation_defined) {
                current_value_ = operation_function_();
                set_value_private(current_value_);
            }
        }

    public:
        /**
         * Creates commandable with initial value
         * @param initial_value initial value to be set, not sent to child objects so should be read and set by children
         * @param result error_t value if error encountered
         */
        explicit commandable(const scheduled_update_t& update_period, const std::string& name)
            : scheduled(update_period, name), operation_defined(false){};

        /**
         * Returns the current value of the commandable as set by get_current_value. The any returned will be of the same type as get_type
         * @param result the returned value copied
         * @return error_t value if error encountered
         */
        T get_current_value() const {
            return current_value_;
        }

        /**
         * The function used to set the value of this commandable. Will be type checked by default then value checked by check_value_private
         * @param value the value to set, must be of type get_type and pass value check
         * @return error_t value if error encountered
         */
        void set_operation(const operation<T>& operation) {
            operation_function_ = operation.get_value;
            operation_defined = true;
        }
        
        void set_operation(const std::function<T()>& operation_function){
            operation_function_ = operation_function;
            operation_defined = true;
        }
//        commandable& operator=(const std::any& value);
    };
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
