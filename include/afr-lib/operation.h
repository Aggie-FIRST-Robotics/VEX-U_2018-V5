#ifndef VEX_U_2018_V5_OPERATION_H
#define VEX_U_2018_V5_OPERATION_H

#include <functional>

#include "afr-lib/nameable.h"

namespace AFR::VexU{
    template <class T>
    class operation : public virtual nameable {
        
        std::function<T()> function_;
        
    public:
        operation(const std::function<T()>& operation_function, const std::string& name)
            : nameable(name), function_(operation_function) {}
            
        void set_function(std::function<T()>& operation_function) {
            function_ = operation_function;
        }
        
        std::function<T()>& get_function() {
            return function_;
        }
    };
}
#endif //VEX_U_2018_V5_OPERATION_H