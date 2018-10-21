#ifndef VEX_U_2018_V5_COMMANDABLE_H
#define VEX_U_2018_V5_COMMANDABLE_H

#include <stdexcept>

namespace AFR::VexU{
    template<typename DataType>
    class invalid_value_error : public std::runtime_error{
    public:
        explicit invalid_value_error(const DataType& value);
    };

    template<typename DataType>
    invalid_value_error<DataType>::invalid_value_error(const DataType& value) : runtime_error(
            "Invalid value:" + value){}

    class commandable_no_temp{

    };

    template<typename DataType>
    class commandable{
        DataType value_;

        virtual void set_value_private(const DataType& value) = 0;
        virtual bool check_value_private(const DataType& value) = 0;

    public:
        explicit commandable(const DataType& initial_value);

        DataType get_current_value();
        void set_value(const DataType& value);
    };

    template<typename DataType>
    commandable<DataType>::commandable(const DataType& initial_value) : value_(initial_value){
        set_value_private(value_);
    }

    template<typename DataType>
    DataType commandable<DataType>::get_current_value(){
        return value_;
    }

    template<typename DataType>
    void commandable<DataType>::set_value(const DataType& value){
        value_ = value;
        if(!check_value_private(value)){
            throw invalid_value_error<DataType>{value};
        }
        set_value_private(value);
    }
}

#endif //VEX_U_2018_V5_COMMANDABLE_H
