#ifndef VEX_U_2018_V5_DEFINES_H
#define VEX_U_2018_V5_DEFINES_H

#include <iostream>
#include <cstring>
#include <sstream>

#include "main.h"

#ifdef AFR_VEXU_NODEBUG
#define AFR_VEXU_CALL(x)
#define AFR_PROS_CALL(x)
#else
#ifdef AFR_VEXU_TEST
#ifdef AFR_VEXU_THROW_ON_ERROR
#define AFR_VEXU_CALL(x){                                                                                           \
    AFR::VexU::error_t internal_error_num_do_not_use = (x)                                                          \
    if(error != AFR::VexU::SUCCESS){                                                                                \
        throw std::runtime_error{"AFR VexU Error encountered: " + std::to_string(internal_error_num_do_not_use)};   \
    }                                                                                                               \
}
#define AFR_PROS_CALL(x){                                                                                           \
    if((x) == PROS_ERR){                                                                                            \
        std::stringstream ss;                                                                                       \
        ss << "Pros error encountered: " << std::strerror(errno);                                                   \
        throw std::runtime_error{ss.str();};                                                                        \
    }                                                                                                               \
}
#else
#define AFR_VEXU_CALL(x){                                                                                           \
    if((x) != SUCCESS){                                                                                             \
        std::cerr << "error: " << error << std::endl;                                                               \
    }                                                                                                               \
}
#define AFR_PROS_CALL(x){                                                                                           \
    if((x) == PROS_ERR){                                                                                            \
        std::cerr << "PROS error: " << std::strerror(errno) << std::endl;                                           \
    }                                                                                                               \
}
#endif
#else
#define AFR_VEXU_CALL(x){                                                                                           \
    if((x) != SUCCESS){                                                                                             \
                                                                                                                    \
    }                                                                                                               \
}
#define AFR_PROS_CALL(x){                                                                                           \
    if((x) == PROS_ERR){                                                                                            \
                                                                                                                    \
    }                                                                                                               \
}
#endif
#endif

#define AFR_VEXU_INTERNAL_CALL(x){                                                                                  \
    error_t internal_error_num_do_not_use = (x);                                                                    \
    if(internal_error_num_do_not_use != SUCCESS){                                                                   \
        return internal_error_num_do_not_use;                                                                       \
    }                                                                                                               \
}
#define AFR_PROS_INTERNAL_CALL(x){                                                                                  \
    if((x) != PROS_ERR){                                                                                            \
        return PROS_ERROR;                                                                                          \
    }                                                                                                               \
}

namespace AFR::VexU{
    enum error_t{
        SUCCESS,            ///No error
        GENERIC_FAILURE,    ///Error occurred, should not be used but replaced with added error to this enum
        INVALID_TYPE,       ///Commandable assigned invalid type
        INVALID_VALUE,      ///Commandable assigned invalid value
        PROS_ERROR          ///Error from pros, read errno
    };
}

#endif //VEX_U_2018_V5_DEFINES_H