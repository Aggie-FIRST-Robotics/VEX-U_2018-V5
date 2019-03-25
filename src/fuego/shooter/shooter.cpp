
#include "fuego/shooter/shooter.h"

namespace AFR::VexU::Fuego::Shooter{

    BaseCommandable::controller_commandable* operator_rumble = nullptr;

    //Readables
    BaseReadable::digital_edge_detector* flywheel_toggle = nullptr;
    BaseReadable::digital_edge_detector* loader_trigger = nullptr;

    state_controller<bool>* shooter_state_controller = nullptr;

    state* rest = nullptr;
    state* spin_up = nullptr;
    state* fire = nullptr;
    state* walk = nullptr;

    std::function<void()> rest_entry{};
    std::function<void()> spin_up_entry{};
    std::function<void()> fire_entry{};
    std::function<void()> fire_exit{};
    std::function<void()> walk_entry{};
    std::function<void()> walk_exit{};


    /////////////////////////////////////////////////////////////////////////////////////////////

    //Readables
    BaseReadable::digital_edge_detector* set_turret_left = nullptr;
    BaseReadable::digital_edge_detector* set_turret_mid = nullptr;
    BaseReadable::digital_edge_detector* set_turret_right = nullptr;
    BaseReadable::digital_edge_detector* set_hood_high = nullptr;
    BaseReadable::digital_edge_detector* set_hood_mid = nullptr;
    BaseReadable::digital_edge_detector* set_hood_low = nullptr;
    BaseReadable::digital_edge_detector* stow = nullptr;

    struct turret_meta {
        double turret_set_point;
        double hood_set_point;
    };
    state_controller<turret_meta>* turret_state_controller = nullptr;

    state* manual = nullptr;
    state* set_point = nullptr;
    state* auto_aim = nullptr;
    state* ready = nullptr;

    std::function<bool()> manual_to_set_point{};
    std::function<bool()> auto_to_ready{};
    std::function<bool()> ready_to_auto{};

    std::function<void()> manual_entry{};
    std::function<void()> manual_exit{};
    std::function<void()> set_point_entry{};
    std::function<void()> auto_entry{};
    std::function<void()> ready_entry{};
    std::function<void()> ready_exit{};

    std::function<double()> hood_set_point{};
    std::function<double()> turret_set_point{};

    std::function<double()> hood_auto_target{};
    std::function<double()> turret_auto_target{};

//    //Shooter searches for target
//    state* auto_aim = nullptr;
//    std::vector<std::pair<std::function<bool()>, state*>> auto_aim_transitions;
//    std::function<void()> auto_aim_entry;
//    std::function<void()> auto_aim_exit;
//
//    //Shooter is locked onto a target
//    state* ready = nullptr;
//    std::vector<std::pair<std::function<bool()>, state*>> ready_transitions;
//    std::function<void()> ready_entry;
//    std::function<void()> ready_exit;

    ////////////////////////////////////////////////////////////////////////////////////////////

    void init() {

        Flywheel::init();
        Turret::init();
        Hood::init();
        Loader::init();

        operator_rumble = new BaseCommandable::controller_commandable(UPDATE_PERIOD,"",pros::E_CONTROLLER_PARTNER,"operator rumble");

        flywheel_toggle = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(FLYWHEEL_TOGGLE);}),"flywheel toggle");
        loader_trigger = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(FIRE);}),"loader trigger");

        shooter_state_controller = new state_controller<bool>{UPDATE_PERIOD,false,"shooter state machine"};

        rest = new state("shooter: rest");
        spin_up = new state("shooter: spin up");
        fire = new state("shooter: fire");
        walk = new state("shooter: walk");

        Flywheel::pid_controller->set_operation(std::function<double()>([](){ return Flywheel::avg_speed->get_average_value();}), shooter_state_controller->get_name());
        Loader::dead_band->set_operation(std::function<double()>([](){ return Loader::encoder->get_scaled_position();}), shooter_state_controller->get_name());
        Flywheel::left_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        Flywheel::right_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        Loader::motor->set_operation(std::function<int16_t()>([](){ return Loader::dead_band->get_deadband_value();}), shooter_state_controller->get_name());

        /////REST
        rest->add_transition(std::function<bool()>([](){ return flywheel_toggle->is_rising_edge();}),spin_up);
        rest->add_transition(std::function<bool()>([](){ return BaseReadable::driver_controller->is_digital_pressed(WALK);}),walk);

        rest_entry = []() -> void{
            Flywheel::left_motor->set_value(0,shooter_state_controller->get_name());
            Flywheel::right_motor->set_value(0,shooter_state_controller->get_name());
            Loader::dead_band->set_target(IDLE_TARGET);
        };
        rest->set_on_state_entry(rest_entry);
        rest->set_on_state_exit(std::function<void()>([](){}));

        shooter_state_controller->add_state(rest);

        /////SPIN UP
        spin_up->add_transition(std::function<bool()>([](){ return Flywheel::avg_speed->get_average_value() > Flywheel::SPEED/2 && loader_trigger->is_rising_edge();}), fire);
        spin_up->add_transition(std::function<bool()>([](){ return flywheel_toggle->is_rising_edge();}),rest);

        spin_up_entry = []() -> void{
            Flywheel::left_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
            Flywheel::right_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        };
        spin_up->set_on_state_entry(spin_up_entry);
        spin_up->set_on_state_exit(std::function<void()>([](){}));

        shooter_state_controller->add_state(spin_up);

        /////FIRE
        fire->add_transition(std::function<bool()>([](){ return Loader::dead_band->is_in_range(LOADER_TOLERANCE);}),spin_up);

        fire_entry = []() -> void {
            Loader::dead_band->set_target(FIRE_TARGET);
        };

        fire_exit = []() -> void {
            Loader::dead_band->set_target(IDLE_TARGET);
        };

        fire->set_on_state_entry(fire_entry);
        fire->set_on_state_exit(fire_exit);

        shooter_state_controller->add_state(fire);

        /////WALK
        walk->add_transition(std::function<bool()>([](){return !BaseReadable::driver_controller->is_digital_pressed(WALK);}),rest);

        walk_entry = []() -> void {
            Loader::dead_band->set_target(WALK_TARGET);
        };

        walk_exit = []() -> void {
            Loader::dead_band->set_target(IDLE_TARGET);
        };

        walk->set_on_state_entry(walk_entry);
        walk->set_on_state_exit(walk_exit);

        shooter_state_controller->add_state(walk);

        shooter_state_controller->set_state(rest);

        /////////////////////////////////////////////////////////////////////////////////////////////

        set_turret_left = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(TURRET_LEFT);}),"set turret left");
        set_turret_mid = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(TURRET_MID);}),"set turret mid");
        set_turret_right = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(TURRET_RIGHT);}),"set turret right");
        set_hood_high = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(HOOD_HIGH);}),"set hood high");
        set_hood_mid = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(HOOD_MID);}),"set hood mid");
        set_hood_low = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(HOOD_LOW);}),"set hood low");
        stow = new BaseReadable::digital_edge_detector
                (std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(STOW);}),"stow");

        turret_state_controller = new state_controller<turret_meta>{UPDATE_PERIOD, {0,0},"turret state machine"};

        manual = new state("turret: manual");
        set_point = new state("turret: set point");
        auto_aim = new state("turret: auto aim");
        ready = new state ("turret: ready");


        Hood::dead_band->set_operation(std::function<double()>([](){ return Hood::encoder->get_scaled_position();}),turret_state_controller->get_name());
        Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::follow_stick->get_bounded_value();}),turret_state_controller->get_name());

        Turret::dead_band->set_operation(std::function<double()>([](){ return Turret::encoder->get_scaled_position();}),turret_state_controller->get_name());
        Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::follow_stick->get_bounded_value();}),turret_state_controller->get_name());

        manual->add_transition(std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(AUTO);}),auto_aim);

        manual_to_set_point = []() -> bool { return set_hood_high->is_rising_edge() || set_hood_mid->is_rising_edge() || set_hood_low->is_rising_edge()
                                      || set_turret_left->is_rising_edge() || set_turret_mid->is_rising_edge() || set_turret_right->is_rising_edge()
                                      || stow->is_rising_edge();};

        manual->add_transition(manual_to_set_point,set_point);

        manual_entry = []() -> void {
            Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::follow_stick->get_bounded_value();}),turret_state_controller->get_name());
            Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::follow_stick->get_bounded_value();}),turret_state_controller->get_name());
        };

        manual_exit = []() -> void {
            Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::dead_band->get_deadband_value();}),turret_state_controller->get_name());
            Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::dead_band->get_deadband_value();}),turret_state_controller->get_name());
        };

        manual->set_on_state_entry(manual_entry);
        manual->set_on_state_exit(manual_exit);

        turret_state_controller->add_state(manual);

        set_point->add_transition(std::function<bool()>([](){
            return (Hood::dead_band->is_in_range(HOOD_TOLERANCE) && Turret::dead_band->is_in_range(TURRET_TOLERANCE)) ||
            abs(BaseReadable::operator_controller->get_analog(TURRET_STICK)) + abs(BaseReadable::operator_controller->get_analog(HOOD_STICK) > STICK_CANCEL_VALUE);}),manual);

        hood_set_point = []() -> double {
            if(BaseReadable::operator_controller->is_digital_pressed(HOOD_HIGH)) {
                turret_state_controller->metadata().hood_set_point = HOOD_HIGH_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(HOOD_MID)) {
                turret_state_controller->metadata().hood_set_point = HOOD_MID_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(HOOD_LOW)) {
                turret_state_controller->metadata().hood_set_point = HOOD_LOW_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(STOW)) {
                turret_state_controller->metadata().hood_set_point = 0;
            }
            return turret_state_controller->metadata().hood_set_point;
        };

        turret_set_point = []() -> double {
            if (BaseReadable::operator_controller->is_digital_pressed(TURRET_LEFT)) {
                turret_state_controller->metadata().turret_set_point = TURRET_LEFT_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(TURRET_MID)) {
                turret_state_controller->metadata().turret_set_point = TURRET_MID_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(TURRET_RIGHT)) {
                turret_state_controller->metadata().turret_set_point = TURRET_RIGHT_TARGET;
            }
            else if (BaseReadable::operator_controller->is_digital_pressed(STOW)) {
                turret_state_controller->metadata().turret_set_point = 0;
            }
            return turret_state_controller->metadata().turret_set_point;
        };

        set_point_entry = []() -> void {
            Hood::dead_band->set_target(hood_set_point);
            Turret::dead_band->set_target(turret_set_point);
        };

        set_point->set_on_state_entry(set_point_entry);
        set_point->set_on_state_exit(std::function<void()>([](){}));

        auto_to_ready = []() -> bool {
            return (Hood::dead_band->is_in_range(HOOD_TOLERANCE) && Turret::dead_band->is_in_range(TURRET_TOLERANCE) && Flywheel::avg_speed->get_average_value() >= 0.95 * Flywheel::SPEED);
        };

        auto_aim->add_transition(std::function<bool()>([](){return !BaseReadable::operator_controller->is_digital_pressed(AUTO);}),manual);
        auto_aim->add_transition(auto_to_ready,ready);

        hood_auto_target = []() -> double {
            //change target by pixel difference from center
            return 0;
        };

        turret_auto_target = []() -> double {
            //change target by pixel difference from center
            return 0;
        };

        auto_entry = []() -> void {
            Hood::dead_band->set_target(hood_auto_target);
            Turret::dead_band->set_target(turret_auto_target);
        };

        auto_aim->set_on_state_entry(auto_entry);
        auto_aim->set_on_state_exit(std::function<void()>([](){}));

        ready_to_auto = []() -> bool {
            return !(Hood::dead_band->is_in_range(HOOD_TOLERANCE) && Turret::dead_band->is_in_range(TURRET_TOLERANCE) && Flywheel::avg_speed->get_average_value() >= 0.95 * Flywheel::SPEED);
        };

        ready->add_transition(ready_to_auto,auto_aim);
        ready->add_transition(std::function<bool()>([](){return !BaseReadable::operator_controller->is_digital_pressed(AUTO);}),manual);

        ready_entry = []() -> void {
            operator_rumble->set_value(".        ",turret_state_controller->get_name());
        };

        ready_exit = []() -> void {
            operator_rumble->set_value("",turret_state_controller->get_name());
        };

        ready->set_on_state_entry(ready_entry);
        ready->set_on_state_exit(ready_exit);

        turret_state_controller->add_state(ready);
        turret_state_controller->add_state(auto_aim);
        turret_state_controller->add_state(set_point);
        turret_state_controller->set_state(manual);
    }

    void destroy(){
        delete shooter_state_controller;
        delete rest;
        delete spin_up;
        delete fire;
        delete walk;
        delete manual;
        delete auto_aim;
    }


}