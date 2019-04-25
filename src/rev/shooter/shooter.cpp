#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"

#include "rev/shooter/shooter.h"

namespace AFR::VexU::Rev::Shooter{

    //Readables
    BaseReadable::digital_debounce* set_high = nullptr;
    BaseReadable::digital_debounce* set_low = nullptr;
    BaseReadable::digital_edge_detector* ball_count = nullptr;
    BaseReadable::digital_edge_detector* zero = nullptr;

    state_controller<shooter_meta>* shooter_state_controller = nullptr;

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

        set_high = new BaseReadable::digital_debounce
                (std::function<bool()>([](){
                    return BaseReadable::driver_controller->is_digital_pressed(HIGH_BUTTON);
                }), BUTTON_DELAY, "^");
        set_low = new BaseReadable::digital_debounce
                (std::function<bool()>([](){ return BaseReadable::driver_controller->is_digital_pressed(LOW_BUTTON); }),
                 BUTTON_DELAY, "V");
        zero = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){ return Puncher::limit_switch->is_pressed(); }),
                 "puncher zero limit switch");
        ball_count = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){ return Rollers::limit_switch->is_pressed(); }), "ball counter");

        shooter_state_controller = new state_controller<shooter_meta>{UPDATE_PERIOD,
                                                                      {ALTITUDE_STOW_TARGET, false, 0, 1, false},
                                                                      "shooter state machine"};

        set_point = new state("set point");
        auto_aim = new state("auto aim");
        ready = new state ("ready");
        cock = new state ("cock");
        double_shot = new state ("double_shot");

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
            // std::cout << (int)shooter_state_controller->metadata().ball_count << std::endl;
            if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON) ||
               BaseReadable::operator_controller->is_digital_pressed(BALL_OUTTAKE_BUTTON)){
                if(ball_count->is_falling_edge()) {
                    if(shooter_state_controller->metadata().ball_count == 0) {
                        shooter_state_controller->metadata().ball_count = 0;
                    }
                    else {
                        shooter_state_controller->metadata().ball_count--;
                    }
                }
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_INTAKE_BUTTON)) {
                if(ball_count->is_falling_edge()) {
                    if(shooter_state_controller->metadata().ball_count == 2) {
                        shooter_state_controller->metadata().ball_count = 2;
                    }
                    else {
                        shooter_state_controller->metadata().ball_count++;
                    }
                    if(shooter_state_controller->metadata().ball_count == 2) {
                        Rollers::top_encoder->tare_position();
                    }
                }
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(RESET_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(RESET_BUTTON)) {
                shooter_state_controller->metadata().ball_count = 0;
            }

            if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON)){
                return -12000;
            }
            else if(shooter_state_controller->metadata().ball_count < 2 && BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON)) {
                return 12000;
            }
            return 0;
        };
        top_intake = []() -> int16_t{
            if(shooter_state_controller->metadata().ball_count < 2) {
                if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON)|| BaseReadable::operator_controller->is_digital_pressed(BALL_OUTTAKE_BUTTON)) {
                    return -12000;
                }
                else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_INTAKE_BUTTON)){
                    return 12000;
                }
            }
            else if(BaseReadable::driver_controller->is_digital_pressed(BALL_SPIT_BUTTON)|| BaseReadable::operator_controller->is_digital_pressed(BALL_OUTTAKE_BUTTON)){
                return -12000;
            }
            else if((BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON) || BaseReadable::operator_controller->is_digital_pressed(BALL_INTAKE_BUTTON)) && Rollers::top_encoder->get_scaled_position() < ROLLER_LIMIT) {
                return 5000;
            }
            return 0;
        };


        Altitude::pid->set_operation(std::function<double()>([](){
            return Altitude::encoder->get_scaled_position();
        }), shooter_state_controller->get_name());
        Altitude::motor->set_operation(std::function<int16_t()>([](){
            return Altitude::pid->get_pid_value();
        }), shooter_state_controller->get_name());

        Puncher::dead_band->set_operation(std::function<double()>([](){
            return Puncher::encoder->get_scaled_position();
        }), shooter_state_controller->get_name());
        Puncher::motor->set_operation(std::function<int16_t()>([](){
            return Puncher::dead_band->get_deadband_value();
        }), shooter_state_controller->get_name());


        Rollers::front_motor->set_operation(front_intake, shooter_state_controller->get_name());
        Rollers::top_motor->set_operation(top_intake, shooter_state_controller->get_name());


        /////Set Point State
        set_point->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            std::cout << "Set entry" << std::endl;
            Altitude::pid->set_target(ALTITUDE_STOW_TARGET);
            if(!(pros::c::competition_get_status() & COMPETITION_AUTONOMOUS)){
                Rollers::front_motor->set_operation(front_intake, shooter_state_controller->get_name());
                Rollers::top_motor->set_operation(top_intake, shooter_state_controller->get_name());
                // Rollers::top_motor->set_operation(top_intake,shooter_state_controller->get_name());
            }
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
        }), ready);

        set_point->add_transition(std::function<bool()>([](){
            if(set_high->is_triggered() && !BaseReadable::driver_controller->is_digital_pressed(LOW_BUTTON) && Rollers::cup_sensor->get_analog_value() < 500){
                Altitude::pid->set_target(ALTITUDE_HIGH_TARGET);
                return true;
            }
            return false;
        }), ready);
        set_point->add_transition(std::function<bool()>([](){
            if(set_high->is_triggered() && set_low->is_triggered() && Rollers::cup_sensor->get_analog_value() < 500){
                Altitude::pid->set_target(ALTITUDE_HIGH_TARGET);
                shooter_state_controller->metadata().is_double = true;
                return true;
            }
            return false;
        }), ready);
        set_point->add_transition(std::function<bool()>([](){
            return Puncher::limit_switch->is_pressed();
        }), cock);

        ready->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            std::cout << "ready entry" << std::endl;
            shooter_state_controller->metadata().timeout = pros::millis() + 250;
        }));

        ready->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "ready exit" << std::endl;
        }));

        ready->add_transition(std::function<bool()>([](){
            return shooter_state_controller->metadata().timeout < pros::millis() && Altitude::pid->is_in_range(ALTITUDE_TOLERANCE);
        }), cock);

        /////Cock stat

        cock->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Cock entry" << std::endl;
            Puncher::motor->set_value(12000, shooter_state_controller->get_name());
            shooter_state_controller->metadata().is_past_thresh = false;
        }));
        cock->set_on_state_exit(std::function<void(state*)>([](state* prev_state){
            std::cout << "Cock Exit" << std::endl;
            if(shooter_state_controller->metadata().ball_count > 0 && shooter_state_controller->metadata().ball_count < 3) {
                shooter_state_controller->metadata().ball_count--;
            }
            Puncher::encoder->tare_position();
            Puncher::dead_band->set_target(COCK_TARGET);
            Puncher::motor->set_operation(std::function<int16_t()>([](){
                if(Puncher::dead_band->is_in_range(PUNCHER_TOLERANCE)) {
                    shooter_state_controller->metadata().is_past_thresh = true;
                }
                if(shooter_state_controller->metadata().is_past_thresh) {
                    return (int16_t)0;
                }
                else {
                    return Puncher::dead_band->get_deadband_value();
                }
            }), shooter_state_controller->get_name());
        }));

        cock->add_transition(std::function<bool()>([](){
            return zero->is_falling_edge();
        }), double_shot);

        /////Double Shot stat

        double_shot->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Double Entry" << std::endl;
            shooter_state_controller->metadata().timeout = pros::millis() + 2000;
            if(!(pros::c::competition_get_status() & COMPETITION_AUTONOMOUS)){
                if(shooter_state_controller->metadata().is_double){
                    std::cout << "Taking a double shot" << std::endl;
                    Altitude::pid->set_target(ALTITUDE_LOW_TARGET);
                    Rollers::top_motor->set_operation(auto_assist_intake, shooter_state_controller->get_name());
                }
                else{
                    Rollers::top_motor->set_operation(top_intake, shooter_state_controller->get_name());
                }
            }
        }));
        double_shot->set_on_state_exit(std::function<void(state*)>([](state* prev_state){
            shooter_state_controller->metadata().is_double = false;
        }));

        double_shot->add_transition(std::function<bool()>([](){
            return Altitude::pid->is_in_range(ALTITUDE_TOLERANCE) && shooter_state_controller->metadata().is_double && Rollers::cup_sensor->get_analog_value() < 500;
        }), ready);
        double_shot->add_transition(std::function<bool()>([](){
            return !shooter_state_controller->metadata().is_double;
        }), set_point);
        double_shot->add_transition(std::function<bool()>([](){
            return shooter_state_controller->metadata().timeout < pros::millis();
        }), set_point);


        shooter_state_controller->add_state(ready);
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

    void reset() {
        Rollers::front_motor->set_operation(front_intake, shooter_state_controller->get_name());
        Rollers::top_motor->set_operation(top_intake, shooter_state_controller->get_name());
    }

}
#pragma clang diagnostic pop