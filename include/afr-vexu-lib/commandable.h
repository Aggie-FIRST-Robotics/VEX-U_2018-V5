#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <any>
#include <stdexcept>

namespace AFR::VexU{
    class invalid_value_error : public std::runtime_error{
    public:
        invalid_value_error();
    };

    class commandable{
    private:
        std::any current_value_;

        virtual void set_value_private(const std::any& value) = 0;
        virtual bool check_value_private(const std::any& value) = 0;

    public:
        explicit commandable(const std::any& initial_value);

        std::any get_current_value() const;

        void set_value(const std::any& value);
        commandable& operator=(const std::any& value);
    };
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
