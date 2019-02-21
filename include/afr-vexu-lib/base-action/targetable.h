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
    class targetable : public action{
    public:
        targetable(scheduled_update_t update_period, commandable* commandable, const std::string& name)
                : action(update_period, commandable, name){}

        virtual void set_target(Read_T target) = 0;
        virtual bool is_in_range(Read_T tolerance) = 0;
    };
}

#endif //VEX_U_2018_V5_TARGETABLE_H
