#include "afr-vexu-lib/base-readable/competition_readable.h"

namespace AFR::VexU::BaseReadable {
    /**
     * Overrides scheduled, updates private variables and period
     * @param delta_seconds new update period
     * @return error_t value if error encountered
     */
    error_t competition_readable::update_private(const double& delta_seconds){
        bool temp_autonomous = pros::competition::is_autonomous();
        AFR_PROS_INTERNAL_CALL(temp_autonomous, PROS_ERR_F);
        autonomous = temp_autonomous;

        bool temp_connected = pros::competition::is_connected();
        AFR_PROS_INTERNAL_CALL(temp_connected, PROS_ERR_F);
        connected = temp_connected;

        bool temp_disabled = pros::competition::is_disabled();
        AFR_PROS_INTERNAL_CALL(temp_disabled, PROS_ERR_F);
        disabled = temp_disabled;

        return SUCCESS;
    }

    /**
     * Creates a competition state readable
     * @param update_period the update period for the readable
     * @param result error_t value if error encountered
     */
    competition_readable::competition_readable(const scheduled_update_t& update_period, AFR::VexU::error_t* result)
            : readable(update_period, 0, result),
              autonomous(pros::competition::is_autonomous()),
              connected(pros::competition::is_connected()),
              disabled(pros::competition::is_disabled()){}

    /**
     * Returns true if robot is autonomous, false if otherwise
     * @param result autonomous
     * @return error_t value if error encountered
     */
    error_t competition_readable::is_autonomous(bool &result) {
        result = autonomous;
        return SUCCESS;
    }

    /**
     * Returns true if robot is connected, false if otherwise
     * @param result connected
     * @return error_t value if error encountered
     */
    error_t competition_readable::is_connected(bool &result) {
        result = connected;
        return SUCCESS;
    }

    /**
     * Returns true if robot is disabled, false if otherwise
     * @param result disabled
     * @return error_t value if error encountered
     */
    error_t competition_readable::is_disabled(bool &result) {
        result = disabled;
        return SUCCESS;
    }
}
