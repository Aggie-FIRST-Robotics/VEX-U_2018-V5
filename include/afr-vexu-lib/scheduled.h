#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <chrono>

namespace AFR::VexU{
    class scheduled{
        std::chrono::steady_clock::time_point next_update_;
        std::chrono::duration<unsigned int, std::milli> update_period_ms_;

        virtual void update_private(const double& delta_seconds) = 0;

    public:
        explicit scheduled(const unsigned int& update_period);

        void update();
    };
}

#endif //VEX_U_2018_V5_SCHEDULED_H
