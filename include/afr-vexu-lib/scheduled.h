#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <unordered_map>
#include "defines.h"
#include "nameable.h"

namespace AFR::VexU{
    typedef int64_t scheduled_update_t;    ///The type for the count of time for scheduled
//    typedef std::milli scheduled_res_t;         ///The type for the unit of time for scheduled

    /**
     * Used to schedule things so that they cna be called constantly without slowing down the processor
     */
    class scheduled: public virtual nameable{
        static std::unordered_map<std::string,scheduled*> scheduled_list;
        uint32_t next_update_;
        uint32_t update_period_;
        bool enabled_;

        /**
         * Overridden to  be whatever happens when update is called following the wait period
         * @param delta_seconds the amount of seconds that have actually passed
         * @return error_t value if error encountered
         */
        virtual void update_private(const double& delta_seconds) = 0;

    public:
        /**
         * Creates a scheduled
         * @param update_period the time period in scheduled_res_t to wait, if 0 will not update
         * @param result error_t value if error encountered
         */
        explicit scheduled(const scheduled_update_t& update_period, const std::string& name);

        ~scheduled();

        static void update_all();
  
        /**
         * Sets if the scheduled should update
         * @param enabled if the scheduled should continue updating
         */  
        void set_enabled(bool enabled);
        bool is_enabled();

        /**
         * Sets the update period
         * @param update_period the update period to set in scheduled_res_t
         * @return error_t value if error encountered
         */
        void set_update_period(scheduled_update_t update_period);
        scheduled_update_t get_update_period() const;
    };

//    /**
//     * Converts time form one unit to usable duration, good for if you want an update period in seconds but the standard time is milli seconds
//     * @tparam T the type of the count
//     * @tparam Unit the unit to convert from such as std::milli
//     * @param amount the number in T of Unit
//     * @param result the converted time read to be passed to scheduled
//     * @return error_t value if error encountered
//     */
//    template<typename T, typename Unit>
//    error_t convert_time(const T& amount, scheduled_update_t& result){
//        result = std::chrono::duration_cast<scheduled_update_t, scheduled_res_t>(
//                std::chrono::duration<T, Unit>{amount});
//        return SUCCESS;
//    }
}

#endif //VEX_U_2018_V5_SCHEDULED_H
