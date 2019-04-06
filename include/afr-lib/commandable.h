#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <stdexcept>
#include <functional>

#include "defines.h"
#include "nameable.h"
#include "scheduled.h"
#include "action.h"
#include "main.h"

namespace AFR::VexU{
    template <class T>
    class commandable : public scheduled {
        /**
         * Used to manage and generalize anything which has a value that needs to be set
         */
    private:
        T set_value_;
        T current_value_;
        std::function<T()> operation_function_;
        bool operation_defined;
        std::string owner_;
        action<T>* action_;

        /**
         * Overridden to assign values to a given commandable
         * @param value the value that is being set to the commandable
         * @param delta_seconds the amount of seconds that have actually passed
         */
        virtual void set_value_private(T value, double delta_seconds) = 0;

        /**
         * Performs the operation function after the wait period and updates the current value
         * @param delta_seconds the amount of seconds that have actually passed
         */
        void update_private(double delta_seconds) override{
            if(operation_defined) {
                current_value_ = operation_function_();
                set_value_private(current_value_, delta_seconds);
            }
        }

        /**
         * Used to update the operation function to return set_value_
         * @return the set value
         */
        T value_function() {
            return set_value_;
        }

    public:
        /**
         * Creates a commandable
         * @param update_period the time period in scheduled_res_t to wait, if 0 will not update
         * @param name the title to be assigned to the object
         */
        explicit commandable(const scheduled_update_t update_period, const std::string& name)
            : nameable(name), scheduled(update_period, name), operation_defined(false), owner_(""), action_(){};

        /**
         * Retrieves the current value of the commandable
         * @return the current value
         */
        T get_current_value() const {
            return current_value_;
        }

        /**
         * Manually changes the operation function that is performed by the commandable
         * @param operation_function the new operation to be assigned
         * @param caller the name of the object which is attempting to change the function
         */
        void set_operation(const std::function<T()>& operation_function, const std::string& caller){
            if(owner_ == "" || owner_ == caller) {
                owner_ = caller;
                operation_function_ = operation_function;
                operation_defined = true;
            }
        }

        /**
         * Currently not implemented
         * @param action
         * @param caller
         * @param dummy
         */
        void set_operation(action<T>* action, const std::string& caller, bool dummy){
            throw std::runtime_error{"Bad call"};
//            action_ = action;
//            set_operation([this]() -> T{
//                return action_->get_value_to_set();
//            }, caller);
        }

        /**
         * Sets a new value to the commandable
         * @param value the new value given to the commandable
         * @param caller the name of the object which is attempting to set the value
         */
        void set_value(const T& value, std::string caller) {
            if(owner_ == "" || owner_ == caller) {
                owner_ = caller;
                set_value_ = value;
                operation_function_ = std::function<T()> ([this](){ return this->value_function(); });
                operation_defined = true;
            }
        }
//        commandable& operator=(const std::any& value);
    };
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
