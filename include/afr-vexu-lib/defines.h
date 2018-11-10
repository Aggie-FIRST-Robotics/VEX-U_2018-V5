#ifndef VEX_U_2018_V5_DEFINES_H
#define VEX_U_2018_V5_DEFINES_H

#include <iostream>

#ifdef AFR_VEXU_NODEBUG
#define AFR_VEXU_CALL(x)
#else
#ifdef AFR_VEXU_TEST
#ifdef AFR_VEXU_THROW_ON_ERROR
#define AFR_VEXU_CALL(x)                                                                        \
                if((x) != SUCCESS){                                                             \
                    throw std::runtime_error{"Error encountered: " + std::to_string(error)};    \
                }
#else
#define AFR_VEXU_CALL(x)                                                                        \
                if((x) != SUCCESS){                                                             \
                    std::cerr << "error: " << error << std::endl;                               \
                }
#endif
#else
#define AFR_VEXU_CALL                                                                           \
            if((x) != SUCCESS){                                                                 \
                                                                                                \
            }
#endif
#endif

#define AFR_VEXU_INTERNAL_CALL(x)                                       \
    error_t internal_error_num_do_not_use = (x);                        \
    if(internal_error_num_do_not_use != SUCCESS){                       \
        return internal_error_num_do_not_use;                           \
    }

namespace AFR::VexU{
    enum error_t{
        SUCCESS,
        GENERIC_FAILURE,
        INVALID_VALUE,      //Commandable assigned invalid value
    };
}

#endif //VEX_U_2018_V5_DEFINES_H