#ifndef VEX_U_2018_V5_DEFINES_H
#define VEX_U_2018_V5_DEFINES_H

#include <iostream>
#include <cstring>
#include <sstream>

#include "main.h"

#ifdef AFR_VEXU_NODEBUG
/**
 * Should wrap any API calls external to the API
 * @param x function call
 */
#define AFR_VEXU_CALL(x)
/**
 * Should wrap any PROS calls external to the API
 * @param x function call
 * @param y error case, usually PROS_ERR or PROS_ERR_F
 */
#define AFR_PROS_CALL(x)
#else
#ifdef AFR_VEXU_TEST
#ifdef AFR_VEXU_THROW_ON_ERROR
/**
 * Should wrap any API calls external to the API
 * @param x function call
 */
#define AFR_VEXU_CALL(x){                                                                                           \
    AFR::VexU::error_t internal_error_num_do_not_use = (x)                                                          \
    if(error != AFR::VexU::SUCCESS){                                                                                \
        throw std::runtime_error{"AFR VexU Error encountered: " + std::to_string(internal_error_num_do_not_use)};   \
    }                                                                                                               \
}
/**
 * Should wrap any PROS calls external to the API
 * @param x function call
 * @param y error case, usually PROS_ERR or PROS_ERR_F
 */
#define AFR_PROS_CALL(x, y){                                                                                        \
    if((x) == (y)){                                                                                                 \
        std::stringstream ss;                                                                                       \
        ss << "Pros error encountered: " << std::strerror(errno);                                                   \
        throw std::runtime_error{ss.str();};                                                                        \
    }                                                                                                               \
}
#else
/**
 * Should wrap any API calls external to the API
 * @param x function call
 */
#define AFR_VEXU_CALL(x){                                                                                           \
    if((x) != SUCCESS){                                                                                             \
        std::cerr << "error: " << error << std::endl;                                                               \
    }                                                                                                               \
}
/**
 * Should wrap any PROS calls external to the API
 * @param x function call
 * @param y error case, usually PROS_ERR or PROS_ERR_F
 */
#define AFR_PROS_CALL(x, y){                                                                                        \
    if((x) == (y)){                                                                                                 \
        std::cerr << "PROS error: " << std::strerror(errno) << std::endl;                                           \
    }                                                                                                               \
}
#endif
#else
/**
 * Should wrap any API calls external to the API
 * @param x function call
 */
#define AFR_VEXU_CALL(x){                                                                                           \
    if((x) != SUCCESS){                                                                                             \
                                                                                                                    \
    }                                                                                                               \
}
/**
 * Should wrap any PROS calls external to the API
 * @param x function call
 * @param y error case, usually PROS_ERR or PROS_ERR_F
 */
#define AFR_PROS_CALL(x, y){                                                                                        \
    if((x) == (y)){                                                                                                 \
                                                                                                                    \
    }                                                                                                               \
}
#endif
#endif

/**
 * Used for API internal calls to itself
 * @param x function call
 */
#define AFR_VEXU_INTERNAL_CALL(x){                                                                                  \
    error_t internal_error_num_do_not_use = (x);                                                                    \
    if(internal_error_num_do_not_use != SUCCESS){                                                                   \
        return internal_error_num_do_not_use;                                                                       \
    }                                                                                                               \
}
/**
 * Used for API internal calls to PROS
 * @param x function call
 * @param y error case
 */
#define AFR_PROS_INTERNAL_CALL(x, y){                                                                               \
    if((x) == (y)){                                                                                                 \
        return PROS_ERROR;                                                                                          \
    }                                                                                                               \
}

namespace AFR::VexU{
    /**
     * Used for errors generated by the API
     */
    enum error_t{
        SUCCESS                  ///No error
        , GENERIC_FAILURE        ///Error occurred, should not be used but replaced with added error to this enum
        , INVALID_TYPE           ///Commandable assigned invalid type
        , INVALID_VALUE          ///Commandable assigned invalid value
        , PROS_ERROR             ///Error from pros, read errno
    };

    typedef uint8_t port_t;
}

#endif //VEX_U_2018_V5_DEFINES_H