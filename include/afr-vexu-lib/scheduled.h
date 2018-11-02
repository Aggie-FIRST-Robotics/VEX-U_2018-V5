#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <chrono>

namespace AFR::VexU{
    typedef unsigned int scheduled_update_t;
    typedef std::milli scheduled_res_t;

    class scheduled{
        std::chrono::steady_clock::time_point next_update_;
        std::chrono::duration<scheduled_update_t, scheduled_res_t> update_period_;

        virtual void update_private(const double& delta_seconds) = 0;

    public:
        explicit scheduled(const scheduled_update_t& update_period);

        void update();
    };

    template<typename T, typename Unit>
    scheduled_update_t convert_time(const T& amount){
        return std::chrono::duration_cast<scheduled_update_t, scheduled_res_t>(std::chrono::duration<T, Unit>{amount});
    }
}

#endif //VEX_U_2018_V5_SCHEDULED_H
