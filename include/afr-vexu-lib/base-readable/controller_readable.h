#ifndef VEX_U_2018_V5_CONTROLLER_READABLE_H
#define VEX_U_2018_V5_CONTROLLER_READABLE_H

#include <unordered_map>

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable{
    class controller_button_readable : public readable{
        pros::Controller controller_;

        std::unordered_map<pros::controller_digital_e_t, bool> digital_map_;
        std::unordered_map<pros::controller_analog_e_t, int32_t> analog_map_;

        error_t update_private(const double& delta_seconds) override;

    public:
        controller_button_readable(const scheduled_update_t& update_period, const pros::controller_id_e_t& controller,
                                   error_t* result = nullptr);

        error_t digital_is_pressed(const pros::controller_digital_e_t& button, bool& result);
        error_t get_analog_value(const pros::controller_analog_e_t& analog, int32_t& result);
    };

    namespace Controller{
        const scheduled_update_t driver_update_period{50};
        const scheduled_update_t operator_update_period{50};

        controller_button_readable* driver_controller;
        controller_button_readable* operator_controller;

        error_t init();
        error_t update();
        error_t destroy();
    }
}

#endif //VEX_U_2018_V5_CONTROLLER_READABLE_H
