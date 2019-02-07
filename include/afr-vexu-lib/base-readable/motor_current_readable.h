#ifndef VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H
#define VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    /**
    * Represents motor current
    */
    class motor_current_readable : public readable {
        port_t port_;

        /**
         * Overrides scheduled, updates private period
         * @param delta_seconds new update period
         * @return error_t value if error encountered
         */
        void update_private(const double& delta_seconds) override;

    public:
        /**
         * Creates a motor current readable
         * @param port smart cable port
         * @param update_period the update period for the readable
         * @param name error_t value if error encountered
         */
        motor_current_readable(port_t port, const std::string& name);

        /**
         * Returns motor current draw
         * @param result current
         * @return error_t value if error encountered
         */
        std::any get_value() override;
    };

}
#endif //VEX_U_2018_V5_MOTOR_CURRENT_READABLE_H
