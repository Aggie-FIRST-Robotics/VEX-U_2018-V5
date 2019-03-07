#ifndef VEX_U_2018_V5_NAMEABLE_H
#define VEX_U_2018_V5_NAMEABLE_H

namespace AFR::VexU{
    class nameable{
        std::string name_;

    public:
        explicit nameable(const std::string& name) : name_(name){};

        std::string get_name(){
            return name_;
        }

        void set_name(const std::string& name){
            name_ = name;
        }
    };
}

#endif //VEX_U_2018_V5_NAMEABLE_H
