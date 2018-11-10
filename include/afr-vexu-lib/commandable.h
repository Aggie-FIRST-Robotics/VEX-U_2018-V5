#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <any>
#include <stdexcept>

#include "defines.h"

namespace AFR::VexU{
//    class invalid_value_error : public std::runtime_error{
//    public:
//        invalid_value_error();
//    };

    class commandable{
    private:
        std::any current_value_;

        virtual error_t set_value_private(const std::any& value) = 0;
        virtual error_t check_value_private(const std::any& value) = 0;

    public:
        explicit commandable(const std::any& initial_value, error_t* result = nullptr);

        error_t get_current_value(std::any& result) const;

        error_t set_value(const std::any& value);
//        commandable& operator=(const std::any& value);
    };
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
