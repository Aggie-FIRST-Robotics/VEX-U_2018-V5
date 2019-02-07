#ifndef VEX_U_2018_V5_COMPETITION_READABLE_H
#define VEX_U_2018_V5_COMPETITION_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents competition status of the robot
    */
    class competition_readable : public readable {
        bool autonomous;
        bool connected;
        bool disabled;

        /**
         * Overrides scheduled, updates private variable and period
         * @param delta_seconds new update period
         * @return error_t value if error encountered
         */
        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a competition state readable
         * @param update_period the update period for the readable
         * @param result error_t value if error encountered
         */
        competition_readable(const scheduled_update_t &update_period, error_t *result);

        /**
         * Returns true if robot is autonomous, false otherwise
         * @param result autonomous
         * @return error_t value if error encountered
         */
        error_t is_autonomous(bool& result);

        /**
         * Returns true if robot is connected, false otherwise
         * @param result connected
         * @return error_t value if error encountered
         */
        error_t is_connected(bool& result);

        /**
         * Returns true if robot is disabled, false otherwise
         * @param result disabled
         * @return error_t value if error encountered
         */
        error_t is_disabled(bool& result);
    };

}
#endif //VEX_U_2018_V5_COMPETITION_READABLE_H
