#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <chrono>

#include "defines.h"

namespace AFR::VexU{
    typedef unsigned int scheduled_update_t;
    typedef std::milli scheduled_res_t;

    class scheduled{
        std::chrono::steady_clock::time_point next_update_;
        std::chrono::duration<scheduled_update_t, scheduled_res_t> update_period_;

        virtual error_t update_private(const double& delta_seconds) = 0;

    public:
        explicit scheduled(const scheduled_update_t& update_period, error_t* result = nullptr);

        error_t update();

        error_t set_update_period(const scheduled_update_t& update_period);
    };

    template<typename T, typename Unit>
    error_t convert_time(const T& amount, scheduled_update_t& result){
        result = std::chrono::duration_cast<scheduled_update_t, scheduled_res_t>(
                std::chrono::duration<T, Unit>{amount});
        return SUCCESS;
    }
}

#endif //VEX_U_2018_V5_SCHEDULED_H
