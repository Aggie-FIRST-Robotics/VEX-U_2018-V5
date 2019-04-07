#ifndef VEX_U_2018_V5_SCHEDULED_H
#define VEX_U_2018_V5_SCHEDULED_H

#include <functional>
#include <unordered_map>

#include "main.h"
#include "afr-lib/defines.h"
#include "afr-lib/nameable.h"

namespace AFR::VexU{
    typedef int64_t scheduled_update_t;    ///The type for the count of time for scheduled

    /**
     * Used to schedule things so that they cna be called constantly without slowing down the processor
     */
    class scheduled: public virtual nameable{
        static std::unordered_map<std::string, scheduled*> scheduled_list_;
        static double constexpr scaling_factor_to_seconds_ = 0.001;

        scheduled_update_t next_update_;
        scheduled_update_t update_period_;
        bool enabled_;

        /**
         * Overridden to  be whatever happens when update is called following the wait period
         * @param delta_seconds the amount of seconds that have actually passed
         * @return error_t value if error encountered
         */
        virtual void update_private(double time) = 0;

        virtual void on_enable(){};

        virtual void on_disable(){};

    public:
        /**
         * Creates a scheduled
         * @param update_period the time period in scheduled_res_t to wait, if 0 will not update
         * @param result error_t value if error encountered
         */
        explicit scheduled(const scheduled_update_t update_period, const std::string& name);

        ~scheduled();

        static void update_all();
  
        /**
         * Sets if the scheduled should update
         * @param enabled if the scheduled should continue updating
         */  
        void set_enabled(bool enabled);
        void enable();
        void disable();
        bool is_enabled();

        /**
         * Sets the update period
         * @param update_period the update period to set in scheduled_res_t
         * @return error_t value if error encountered
         */
        void set_update_period(scheduled_update_t update_period);
        scheduled_update_t get_update_period() const;
    };
}

#endif //VEX_U_2018_V5_SCHEDULED_H
