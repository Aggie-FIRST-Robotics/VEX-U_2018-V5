#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <stdexcept>
#include <functional>

#include "afr-lib/defines.h"
#include "afr-lib/nameable.h"
#include "afr-lib/scheduled.h"
#include "afr-lib/action.h"
#include "main.h"

namespace AFR::VexU{
    template <class T>
    class commandable : public scheduled {
    private:
        T set_value_;
        T current_value_;
        std::function<T()> operation_function_;
        bool operation_defined;
        std::string owner_;
        action<T>* action_;

        virtual void set_value_private(T value, double delta_seconds) = 0;

        void update_private(double delta_seconds) override{
            if(operation_defined) {
                current_value_ = operation_function_();
                set_value_private(current_value_, delta_seconds);
            }
        }
        
        T value_function() {
            return set_value_;
        }

    public:
        explicit commandable(const scheduled_update_t update_period, const std::string& name)
            : nameable(name), scheduled(update_period, name), operation_defined(false), owner_(""), action_(){};

        T get_current_value() const {
            return current_value_;
        }
        
        void set_operation(const std::function<T()>& operation_function, const std::string& caller){
            if(owner_ == "" || owner_ == caller) {
                owner_ = caller;
                operation_function_ = operation_function;
                operation_defined = true;
            }
        }
        void set_operation(action<T>* action, const std::string& caller, bool dummy){
            throw std::runtime_error{"Bad call"};
//            action_ = action;
//            set_operation([this]() -> T{
//                return action_->get_value_to_set();
//            }, caller);
        }
        
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
