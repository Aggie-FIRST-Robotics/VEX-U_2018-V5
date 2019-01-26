#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::BaseReadable{
    error_t controller_readable::update_private(const double& delta_seconds){
        for(auto& value : digital_map_){
            value.second = controller_.get_digital(value.first) != 0;
        }
        for(auto& value : analog_map_){
            value.second = controller_.get_analog(value.first);
        }
        return SUCCESS;
    }

    controller_readable::controller_readable(const AFR::VexU::scheduled_update_t& update_period,
                                             const pros::controller_id_e_t& controller,
                                             AFR::VexU::error_t* result) : readable(update_period,
                                                                                                  nullptr, result),
                                                                                         controller_(controller),
                                                                                         digital_map_(), analog_map_(){
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_L1, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_L2, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_R1, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_R2, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_UP, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_DOWN, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_LEFT, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_RIGHT, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_X, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_B, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_Y, false));
        digital_map_.insert(std::make_pair(pros::E_CONTROLLER_DIGITAL_A, false));

        analog_map_.insert(std::make_pair(pros::E_CONTROLLER_ANALOG_LEFT_X, 0));
        analog_map_.insert(std::make_pair(pros::E_CONTROLLER_ANALOG_LEFT_Y, 0));
        analog_map_.insert(std::make_pair(pros::E_CONTROLLER_ANALOG_RIGHT_X, 0));
        analog_map_.insert(std::make_pair(pros::E_CONTROLLER_ANALOG_RIGHT_Y, 0));
    }

    error_t controller_readable::digital_is_pressed(const pros::controller_digital_e_t& button, bool& result){
        result = digital_map_.at(button);
        return SUCCESS;
    }

    error_t controller_readable::get_analog_value(const pros::controller_analog_e_t& analog, int32_t& result){
        result = analog_map_.at(analog);
        return SUCCESS;
    }

    namespace Controller{
        controller_readable* driver_controller = nullptr;
        controller_readable* operator_controller = nullptr;

        error_t init(){
            driver_controller = new controller_readable{driver_update_period, pros::E_CONTROLLER_MASTER};
            operator_controller = new controller_readable{operator_update_period, pros::E_CONTROLLER_PARTNER};
            return SUCCESS;
        }

        error_t update(){
            AFR_VEXU_INTERNAL_CALL(driver_controller->update());
            AFR_VEXU_INTERNAL_CALL(operator_controller->update());
            return SUCCESS;
        }

        error_t destroy(){
            delete (driver_controller);
            delete (operator_controller);
            return SUCCESS;
        }
    }
}
