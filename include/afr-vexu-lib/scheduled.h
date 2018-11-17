#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <chrono>

#include "defines.h"

namespace AFR::VexU{
    typedef unsigned int scheduled_update_t;    ///The tye for the count of time for scheduled
    typedef std::milli scheduled_res_t;         ///The type for the unit of time for scheduled

    /**
     * Used to schedule things so that they cna be called constantly without slowing down the processor
     */
    class scheduled{
        std::chrono::steady_clock::time_point next_update_;
        std::chrono::duration<scheduled_update_t, scheduled_res_t> update_period_;

        /**
         * Overridden to  be whatever happens when update is called following the wait period
         * @param delta_seconds the amount of seconds that have actually passed
         * @return error_t value if error encountered
         */
        virtual error_t update_private(const double& delta_seconds) = 0;

    public:
        /**
         * Creates a scheduled
         * @param update_period the time period in scheduled_res_t to wait
         * @param result error_t value if error encountered
         */
        explicit scheduled(const scheduled_update_t& update_period, error_t* result = nullptr);

        /**
         * The function that is called to update the scheduled, calls update_private if the time period has passed
         * @return error_t value if error encountered
         */
        error_t update();

        /**
         * Sets the update period
         * @param update_period the update period to set in scheduled_res_t
         * @return error_t value if error encountered
         */
        error_t set_update_period(const scheduled_update_t& update_period);
    };

    /**
     * Converts time form one unit to usable duration, good for if you want an update period in seconds but the standard time is milli seconds
     * @tparam T the type of the count
     * @tparam Unit the unit to convert from such as std::milli
     * @param amount the number in T of Unit
     * @param result the converted time read to be passed to scheduled
     * @return error_t value if error encountered
     */
    template<typename T, typename Unit>
    error_t convert_time(const T& amount, scheduled_update_t& result){
        result = std::chrono::duration_cast<scheduled_update_t, scheduled_res_t>(
                std::chrono::duration<T, Unit>{amount});
        return SUCCESS;
    }
}

#endif //VEX_U_2018_V5_SCHEDULED_H
