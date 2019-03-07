#ifndef VEX_U_2018_V5_NAMEABLE_H
#define VEX_U_2018_V5_NAMEABLE_H

#include <unordered_map>
#include <string>

namespace AFR::VexU{
    class nameable{

        std::string name_;
        static std::unordered_map<std::string, nameable*> nameables_;

    public:
        explicit nameable(const std::string& name);

        ~nameable();

        std::string get_name(){
            return name_;
        }

        void set_name(const std::string& name);

        static nameable* find_nameable(const std::string& name);
    };
}

#endif //VEX_U_2018_V5_NAMEABLE_H
