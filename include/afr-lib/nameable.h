#ifndef VEX_U_2018_V5_NAMEABLE_H
#define VEX_U_2018_V5_NAMEABLE_H

#include <unordered_map>
#include <string>

namespace AFR::VexU{
    class nameable{
        /**
        * Represents something that shall be named on the robot
        */


        std::string name_;
        static std::unordered_map<std::string, nameable*> nameables_;

    public:
        /**
         * Creates nameable with adjustable name
         * @param name to be assigned to the object
         */
        explicit nameable(const std::string& name);

        ~nameable();

        /**
        *Gets the name of the object
        */
        std::string get_name(){
            return name_;
        }

        /**
        *Sets the name of the object
        *@param string name the name of the object
        */
        void set_name(const std::string& name);

        /**
        *Returns the nameable of an object with given name\
        *@param string name the name of the object
        */
        static nameable* find_nameable(const std::string& name);
    };
}

#endif //VEX_U_2018_V5_NAMEABLE_H
