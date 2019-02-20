#ifndef VEX_U_2018_V5_CONTROLLER_READABLE_H
#define VEX_U_2018_V5_CONTROLLER_READABLE_H

#include <unordered_map>

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    class controller_readable : public readable{
        void update_private(const double& delta_seconds) override;

    protected:
        pros::controller_id_e_t controller_;

    public:
        explicit controller_readable(pros::controller_id_e_t controller);
    };

    class controller_analog_readable : public controller_readable{
        pros::controller_analog_e_t channel_;

    public:
        controller_analog_readable(pros::controller_id_e_t controller, pros::controller_analog_e_t channel);

        int32_t get_position();

        std::any get_value() override;
    };

    class controller_digital_readable : public controller_readable{
        pros::controller_digital_e_t button_;

    public:
        controller_digital_readable(pros::controller_id_e_t controller, pros::controller_digital_e_t button);

        bool is_pressed();
        bool is_rising_edge();

        std::any get_value() override;
    };

    controller_analog_readable*
    get_controller_analog_readable(pros::controller_id_e_t controller, pros::controller_analog_e_t channel);
    controller_digital_readable* get_controller_digital_readable(pros::controller_id_e_t controller,
                                                                 pros::controller_digital_e_t button);

    void destroy_controllers();
}

#endif //VEX_U_2018_V5_CONTROLLER_READABLE_H
