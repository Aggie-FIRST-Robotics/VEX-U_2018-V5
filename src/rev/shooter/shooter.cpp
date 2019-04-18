
#include "rev/shooter/shooter.h"

namespace AFR::VexU::Rev::Shooter{

    //Readables
    BaseReadable::digital_debounce* set_high = nullptr;
    BaseReadable::digital_debounce* set_low = nullptr;
    BaseReadable::digital_edge_detector* zero = nullptr;
    Vision::vision_targeting* vision = nullptr;

    struct turret_meta {
        double altitude_set_point;
        bool is_double;
        unsigned long timeout;
    };
    state_controller<turret_meta>* shooter_state_controller = nullptr;

    state* set_point = nullptr;
    state* auto_aim = nullptr;
    state* ready = nullptr;
    state* cock = nullptr;
    state* double_shot = nullptr;

    BaseCommandable::controller_commandable* operator_rumble = nullptr;

    std::function<int16_t()> auto_assist_intake;
    std::function<int16_t()> front_intake;
    std::function<int16_t()> top_intake;
    //memes

    void init() {
        Rollers::init();
        Altitude::init();
        Puncher::init();

        auto_assist_intake = []() -> int16_t{ 
            if(BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_INTAKE_BUTTON)){
                return 12000;
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_OUTTAKE_BUTTON)){
                return -12000;
            }
            else if(Rollers::cup_sensor->get_analog_value() > 500){
                return 12000;
            }
            else {
                return 0;
            }
        };
        front_intake = []() -> int16_t{ 
            if(BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON)){
                return 12000;
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON)){
                return -12000;
            }
            return 0;
        };
        top_intake = []() -> int16_t{ 
            if(BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_INTAKE_BUTTON)){
                return 12000;
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON)|| BaseReadable::operator_controller->is_digital_pressed(BALL_OUTTAKE_BUTTON)){
                return -12000;
            }
            return 0;
        };

        set_high = new BaseReadable::digital_debounce
                (std::function<bool()>([](){return BaseReadable::driver_controller->is_digital_pressed(HIGH_BUTTON);}),BUTTON_DELAY,"^");
        set_low = new BaseReadable::digital_debounce
                (std::function<bool()>([](){return BaseReadable::driver_controller->is_digital_pressed(LOW_BUTTON);}),BUTTON_DELAY,"V");
        zero = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return Puncher::limit_switch->is_pressed();}),"puncher zero limit switch");


        vision = new Vision::vision_targeting("vision");

        shooter_state_controller = new state_controller<turret_meta>{UPDATE_PERIOD, {ALTITUDE_STOW_TARGET,false,0},"shooter state machine"};

        set_point = new state("set point");
        auto_aim = new state("auto aim");
        ready = new state ("ready");
        cock = new state ("cock");
        double_shot = new state ("double_shot");


        Altitude::pid->set_operation(std::function<double()>([](){
            return Altitude::encoder->get_scaled_position();
        }),shooter_state_controller->get_name());
        Altitude::motor->set_operation(std::function<int16_t()>([](){
            return Altitude::pid->get_pid_value();
        }),shooter_state_controller->get_name());

        Puncher::dead_band->set_operation(std::function<double()>([](){
            return Puncher::encoder->get_scaled_position();
        }),shooter_state_controller->get_name());
        Puncher::motor->set_operation(std::function<int16_t()>([](){
            return Puncher::dead_band->get_deadband_value();
        }),shooter_state_controller->get_name());

        vision->set_operation(std::function<Vision::encoder_tuple()>([](){
            Vision::encoder_tuple given;
            given.altitude = Altitude::encoder->get_scaled_position();
            given.azimuth = 0;
            return given;
        }),shooter_state_controller->get_name());



        Rollers::front_motor->set_operation(front_intake,shooter_state_controller->get_name());
        Rollers::top_motor->set_operation(top_intake,shooter_state_controller->get_name());

        /////Set Point State
        set_point->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            std::cout << "Set entry" << std::endl;
            Altitude::pid->set_target(ALTITUDE_STOW_TARGET);
            Rollers::top_motor->set_operation(top_intake,shooter_state_controller->get_name());
        }));

        set_point->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Set exit" << std::endl;
        }));

        set_point->add_transition(std::function<bool()>([](){
            if(set_low->is_triggered() && !BaseReadable::driver_controller->is_digital_pressed(HIGH_BUTTON) && Rollers::cup_sensor->get_analog_value() < 500){
                Altitude::pid->set_target(ALTITUDE_LOW_TARGET);
                return true;
            }
            return false;
        }),ready);
        set_point->add_transition(std::function<bool()>([](){
            if(set_high->is_triggered() && !BaseReadable::driver_controller->is_digital_pressed(LOW_BUTTON) && Rollers::cup_sensor->get_analog_value() < 500){
                Altitude::pid->set_target(ALTITUDE_HIGH_TARGET);
                return true;
            }
            return false;
        }),ready);
        set_point->add_transition(std::function<bool()>([](){
            if(set_high->is_triggered() && set_low->is_triggered() && Rollers::cup_sensor->get_analog_value() < 500){
                Altitude::pid->set_target(ALTITUDE_HIGH_TARGET);
                shooter_state_controller->metadata().is_double = true;
                return true;
            }
            return false;
        }),ready);
        set_point->add_transition(std::function<bool()>([](){
            return Puncher::limit_switch->is_pressed();
        }),cock);

        ready->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            std::cout << "ready entry" << std::endl;
            shooter_state_controller->metadata().timeout = pros::millis() + 250;
        }));

        ready->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "ready exit" << std::endl;
        }));

        ready->add_transition(std::function<bool()>([](){
            return shooter_state_controller->metadata().timeout < pros::millis() && Altitude::pid->is_in_range(ALTITUDE_TOLERANCE);
        }),cock);

        /////Auto Aim State

        vision->disable();

        operator_rumble = new BaseCommandable::controller_commandable(UPDATE_PERIOD,"",pros::E_CONTROLLER_PARTNER,"operator rumble");

        // auto_aim->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
        //     vision->enable();
        //     Altitude::pid->set_target(std::function<double()>([](){
        //         if(vision->has_target_rect()) {
        //             Vision::encoder_tuple auto_encoder_change = vision->get_encoder_setpoints();
        //             if (Altitude::encoder->get_scaled_position() + auto_encoder_change.altitude > Altitude::ENCODER_LIMIT) {
        //                 return Altitude::ENCODER_LIMIT;
        //             } else if (Altitude::encoder->get_scaled_position() + auto_encoder_change.altitude < 0) {
        //                 return 0.0;
        //             } else {
        //                 return Altitude::encoder->get_scaled_position() + auto_encoder_change.altitude;
        //             }
        //         }
        //         else {
        //             return Altitude::encoder->get_scaled_position();
        //         }
        //     }));
        // }));

        // auto_aim->set_on_state_exit(std::function<void(state*)>([](state* next_state){
        //     vision->purge_target_list();
        //     vision->disable();
        // }));

        // auto_aim->add_transition(std::function<bool()>([](){
        //     return !BaseReadable::operator_controller->is_digital_pressed(AUTO_BUTTON);
        // }),set_point);

        /////Cock stat

        cock->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Cock entry" << std::endl;
            Puncher::motor->set_value(12000,shooter_state_controller->get_name());
        }));
        cock->set_on_state_exit(std::function<void(state*)>([](state* prev_state){
            std::cout << "Cock Exit" << std::endl;
            Puncher::encoder->tare_position();
            zero->set_last_read(true);
            Puncher::dead_band->set_target(std::function<double()>([](){
                if(zero->is_falling_edge())
                return COCK_TARGET;
            }));
            Puncher::motor->set_operation(std::function<int16_t()>([](){
                if(Puncher::dead_band->is_in_range(PUNCHER_TOLERANCE)) {
                    return (int16_t)0;
                }
                return Puncher::dead_band->get_deadband_value();
            }),shooter_state_controller->get_name());
        }));

        cock->add_transition(std::function<bool()>([](){
            return zero->is_falling_edge();
        }), double_shot);

        /////Double Shot state

        double_shot->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            shooter_state_controller->metadata().timeout = pros::millis() + 2000;
            if(shooter_state_controller->metadata().is_double){
                std::cout << "Taking a double shot" << std::endl;
                Altitude::pid->set_target(ALTITUDE_LOW_TARGET);
                Rollers::top_motor->set_operation(auto_assist_intake,shooter_state_controller->get_name());
            }
        }));
        double_shot->set_on_state_exit(std::function<void(state*)>([](state* prev_state){
            shooter_state_controller->metadata().is_double = false;
        }));

        double_shot->add_transition(std::function<bool()>([](){
            return Altitude::pid->is_in_range(ALTITUDE_TOLERANCE) && Puncher::dead_band->is_in_range(PUNCHER_TOLERANCE) && shooter_state_controller->metadata().is_double && Rollers::cup_sensor->get_analog_value() < 500;
        }), ready);
        double_shot->add_transition(std::function<bool()>([](){
            return !shooter_state_controller->metadata().is_double;
        }), set_point);
        double_shot->add_transition(std::function<bool()>([](){
            return shooter_state_controller->metadata().timeout < pros::millis();
        }), set_point);


        shooter_state_controller->add_state(ready);
        shooter_state_controller->add_state(set_point);
        shooter_state_controller->add_state(auto_aim);
        shooter_state_controller->add_state(set_point);
        shooter_state_controller->add_state(cock);
        shooter_state_controller->add_state(double_shot);
        shooter_state_controller->set_state(cock);
    }

    void destroy(){
        Altitude::destroy();
        Puncher::destroy();
        delete shooter_state_controller;
        delete ready;
        delete auto_aim;
        delete set_point;
        delete cock;
        delete double_shot;
    }


}