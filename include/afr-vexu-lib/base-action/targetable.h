#ifndef VEX_U_2018_V5_TARGETABLE_H
#define VEX_U_2018_V5_TARGETABLE_H

namespace AFR::VexU::BaseAction{
    template<typename T>
    T abs(T val){
        if(val < 0){
            return -val;
        }
        return val;
    }

    template<typename Read_T>
    class targetable : public action, public commandable{
        void set_value_private(const std::any& value) override{
            set_target(std::any_cast<Read_T>(value));
        }

        void check_value_private(const std::any& value) override{}
    public:
        targetable(scheduled_update_t update_period, commandable* commandable, Read_T initial_value,
                   const std::string& name)
                : action(update_period, commandable, name), commandable::commandable(initial_value, name){}

        virtual void set_target(Read_T target) = 0;
        virtual bool is_in_range(Read_T tolerance) = 0;

        std::type_index get_type() const override{
            return typeid(Read_T);
        }
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
