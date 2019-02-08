#include "afr-vexu-lib/base-readable/controller_readable.h"

namespace AFR::VexU::BaseReadable{
    std::unordered_map<pros::controller_analog_e_t, controller_analog_readable*> driver_analogs{};
    std::unordered_map<pros::controller_digital_e_t, controller_digital_readable*> driver_digitals{};
    std::unordered_map<pros::controller_analog_e_t, controller_analog_readable*> operator_analogs{};
    std::unordered_map<pros::controller_digital_e_t, controller_digital_readable*> operator_digitals{};

    void controller_readable::update_private(const double& delta_seconds){}

    controller_readable::controller_readable(pros::controller_id_e_t controller)
            : readable(0, nullptr, (controller == pros::E_CONTROLLER_MASTER ? "driver_readable" : "operator_readable")),
              controller_(controller){}

    controller_analog_readable::controller_analog_readable(pros::controller_id_e_t controller,
                                                           pros::controller_analog_e_t channel)
            : controller_readable(controller), channel_(channel){}

    std::any controller_analog_readable::get_value(){
        return get_position();
    }

    int32_t controller_analog_readable::get_position(){
        return pros::c::controller_get_analog(controller_, channel_);
    }

    controller_digital_readable::controller_digital_readable(pros::controller_id_e_t controller,
                                                             pros::controller_digital_e_t button)
            : controller_readable(controller), button_(button){}

    std::any controller_digital_readable::get_value(){
        return is_pressed();
    }

    bool controller_digital_readable::is_pressed(){
        return pros::c::controller_get_digital(controller_, button_) == 1;
    }

    controller_analog_readable*
    get_controller_analog_readable(pros::controller_id_e_t controller, pros::controller_analog_e_t channel){
        std::unordered_map<pros::controller_analog_e_t, controller_analog_readable*>* map = nullptr;
        if(controller == pros::E_CONTROLLER_MASTER){
            map = &driver_analogs;
        }
        else{
            map = &operator_analogs;
        }
        return map->emplace(channel, new controller_analog_readable{controller, channel}).first->second;
    }

    controller_digital_readable*
    get_controller_digital_readable(pros::controller_id_e_t controller, pros::controller_digital_e_t button){
        std::unordered_map<pros::controller_digital_e_t, controller_digital_readable*>* map = nullptr;
        if(controller == pros::E_CONTROLLER_MASTER){
            map = &driver_digitals;
        }
        else{
            map = &operator_digitals;
        }
        return map->emplace(button, new controller_digital_readable{controller, button}).first->second;
    }

    void destroy_controllers(){
        for(auto analog : driver_analogs){
            delete (analog.second);
        }
        for(auto digital : driver_digitals){
            delete (digital.second);
        }
        for(auto analog : operator_analogs){
            delete (analog.second);
        }
        for(auto digital : operator_digitals){
            delete (digital.second);
        }
    }
}
