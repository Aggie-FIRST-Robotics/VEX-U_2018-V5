#ifndef VEX_U_2018_V5_DEFINES_H
#define VEX_U_2018_V5_DEFINES_H

#include <iostream>
#include <cstring>
#include <sstream>

namespace AFR::VexU{
    template<typename T>
    bool in_range(const T& lower, const T& val, const T& upper){
        return val >= lower && val <= upper;
    }

    typedef uint8_t port_t;
}

#define AFR_TRY(x, y){                                                                                                 \
    try{                                                                                                            \
        (x);                                                                                                        \
    }                                                                                                               \
    catch(std::exception& e){                                                                                       \
        std::cerr << "Error: " << e.what() << std::endl;                                                             \
        std::cerr << "Line " << __LINE__ << " In file " << __FILE__ << std::endl;                                  \
        std::cerr << (y) << std::endl;\
        throw e;\
    }                                                                                                               \
}

#endif //VEX_U_2018_V5_DEFINES_H