

#include "fuego/shooter/shooter.h"

namespace AFR::VexU::Fuego::Shooter{

    ///////////////////////////////////////////////////////////////////////////////////////////

    BaseCommandable::controller_commandable* operator_rumble = nullptr;

    //Readables
    BaseReadable::digital_edge_detector* flywheel_toggle = nullptr;
    BaseReadable::digital_edge_detector* loader_trigger = nullptr;

    state_controller<bool>* shooter_state_controller = nullptr;

    state* rest = nullptr;
    state* spin_up = nullptr;
    state* fire = nullptr;
    state* walk = nullptr;
    state* zero_dick = nullptr;

    std::function<void(state*)> rest_entry{};
    std::function<void(state*)> spin_up_entry{};
    std::function<void(state*)> fire_entry{};
    std::function<void(state*)> fire_exit{};
    std::function<void(state*)> walk_entry{};
    std::function<void(state*)> walk_exit{};


    /////////////////////////////////////////////////////////////////////////////////////////////

    //Readables
    BaseReadable::digital_edge_detector* walker_button = nullptr;
    BaseReadable::digital_edge_detector* set_turret_left = nullptr;
    BaseReadable::digital_edge_detector* set_turret_mid = nullptr;
    BaseReadable::digital_edge_detector* set_turret_right = nullptr;
    BaseReadable::digital_edge_detector* set_hood_high = nullptr;
    BaseReadable::digital_edge_detector* set_hood_mid = nullptr;
    BaseReadable::digital_edge_detector* set_hood_low = nullptr;
    BaseReadable::digital_edge_detector* stow = nullptr;
    Vision::vision_targeting* vision = nullptr;

    
    state_controller<turret_meta>* turret_state_controller = nullptr;

    state* manual = nullptr;
    state* set_point = nullptr;
    state* auto_aim = nullptr;
    state* ready = nullptr;

    std::function<bool()> manual_to_set_point{};
    std::function<bool()> auto_to_ready{};
    std::function<bool()> ready_to_auto{};

    std::function<void(state*)> manual_entry{};
    std::function<void(state*)> manual_exit{};
    std::function<void(state*)> set_point_entry{};
    std::function<void(state*)> auto_entry{};
    std::function<void(state*)> ready_entry{};
    std::function<void(state*)> ready_exit{};

    std::function<double()> hood_set_point{};
    std::function<double()> turret_set_point{};

    std::function<double()> hood_auto_target{};
    std::function<double()> turret_auto_target{};

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
        zero_dick = new state("shooter: zero_dick");

        walker_button = new BaseReadable::digital_edge_detector(pros::E_CONTROLLER_MASTER,WALK,"walker button");

        Flywheel::pid_controller->set_operation(std::function<double()>([](){
            double val = Flywheel::avg_speed->get_average_value();
            std::cout << val << std::endl;
            return val;
        }), shooter_state_controller->get_name());
        Loader::dead_band->set_operation(std::function<double()>([](){
            return Loader::encoder->get_scaled_position();}), shooter_state_controller->get_name());
        Flywheel::left_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        Flywheel::right_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        Loader::motor->set_operation(std::function<int16_t()>([](){ return Loader::dead_band->get_deadband_value();}), shooter_state_controller->get_name());

        /////REST
        rest->add_transition(std::function<bool()>([](){
            return flywheel_toggle->is_rising_edge();
        }),spin_up);
        rest->add_transition(std::function<bool()>([](){
            return walker_button->is_rising_edge();
        }),walk);

        rest_entry = [](state* prev_state) -> void{
            Flywheel::pid_controller->disable();
            Flywheel::left_motor->set_value(0,shooter_state_controller->get_name());
            Flywheel::right_motor->set_value(0,shooter_state_controller->get_name());
            Loader::dead_band->set_target(IDLE_TARGET);
        };
        rest->set_on_state_entry(rest_entry);
        rest->set_on_state_exit(std::function<void(state*)>([](state* next_state){}));

        shooter_state_controller->add_state(rest);

        /////SPIN UP
        spin_up->add_transition(std::function<bool()>([](){
            return Flywheel::avg_speed->get_average_value() > Flywheel::SPEED/2 && loader_trigger->is_rising_edge();
        }), fire);
        spin_up->add_transition(std::function<bool()>([](){
            return flywheel_toggle->is_rising_edge();
        }),rest);

        spin_up_entry = [](state* prev_state) -> void{
            Flywheel::pid_controller->enable();
            Flywheel::left_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
            Flywheel::right_motor->set_operation(std::function<int16_t()>([](){return Flywheel::pid_controller->get_pid_value();}),shooter_state_controller->get_name());
        };
        spin_up->set_on_state_entry(spin_up_entry);
        spin_up->set_on_state_exit(std::function<void(state*)>([](state* next_state){}));

        shooter_state_controller->add_state(spin_up);

        /////FIRE
        fire->add_transition(std::function<bool()>([](){
            return Loader::dead_band->is_in_range(LOADER_TOLERANCE) && Flywheel::pid_controller->is_enabled();
        }),spin_up);

        fire->add_transition(std::function<bool()>([](){
            return Loader::dead_band->is_in_range(LOADER_TOLERANCE) && !Flywheel::pid_controller->is_enabled();
        }),rest);

        fire_entry = [](state* prev_state) -> void {
            Loader::dead_band->set_target(FIRE_TARGET);
        };

        fire_exit = [](state* next_state) -> void {
            Loader::dead_band->set_target(IDLE_TARGET);
        };

        fire->set_on_state_entry(fire_entry);
        fire->set_on_state_exit(fire_exit);

        shooter_state_controller->add_state(fire);

        /////WALK
        walk->add_transition(std::function<bool()>([](){
            return walker_button->is_rising_edge();
        }),rest);

        walk->add_transition(std::function<bool()>([](){
            return BaseReadable::driver_controller->is_digital_pressed(DOWN_BUTTON);
        }),fire);

        walk_entry = [](state* prev_state) -> void {
            Loader::dead_band->set_target(WALK_TARGET);
        };

        walk_exit = [](state* next_state) -> void {
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
        vision = new Vision::vision_targeting("vision");
        vision->set_team(Vision::vision_targeting::RED);

        turret_state_controller = new state_controller<turret_meta>{UPDATE_PERIOD, {0,0},"turret state machine"};

        manual = new state("turret: manual");
        set_point = new state("turret: set point");
        auto_aim = new state("turret: auto aim");
        ready = new state ("turret: ready");


        Hood::pid->set_operation(std::function<double()>([](){ return Hood::encoder->get_scaled_position();}),turret_state_controller->get_name());
        Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::follow_stick->get_bounded_value();}),turret_state_controller->get_name());

        Turret::pid->set_operation(std::function<double()>([](){ return Turret::encoder->get_scaled_position();}),turret_state_controller->get_name());
        Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::follow_stick->get_bounded_value();}),turret_state_controller->get_name());

        vision->set_operation(std::function<Vision::encoder_tuple()>([](){
            Vision::encoder_tuple given;
            given.altitude = Hood::encoder->get_scaled_position();
            given.azimuth = Turret::encoder->get_scaled_position();
            return given;
        }),turret_state_controller->get_name());

        manual->add_transition(std::function<bool()>([](){return BaseReadable::operator_controller->is_digital_pressed(AUTO);}),auto_aim);

        manual_to_set_point = []() -> bool { return set_hood_high->is_rising_edge() || set_hood_mid->is_rising_edge() || set_hood_low->is_rising_edge()
                                      || set_turret_left->is_rising_edge() || set_turret_mid->is_rising_edge() || set_turret_right->is_rising_edge()
                                      || stow->is_rising_edge();};

        manual->add_transition(manual_to_set_point,set_point);

        manual_entry = [](state* prev_state) -> void {
            Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::follow_stick->get_bounded_value();}),turret_state_controller->get_name());
            Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::follow_stick->get_bounded_value();}),turret_state_controller->get_name());
        };

        manual_exit = [](state* next_state) -> void {
            Hood::motor->set_operation(std::function<int16_t()>([](){return Hood::pid->get_pid_value();}),turret_state_controller->get_name());
            Turret::motor->set_operation(std::function<int16_t()>([](){return Turret::pid->get_pid_value();}),turret_state_controller->get_name());
        };

        manual->set_on_state_entry(manual_entry);
        manual->set_on_state_exit(manual_exit);

        turret_state_controller->add_state(manual);

        set_point->add_transition(std::function<bool()>([](){
            return (Hood::pid->is_in_range(HOOD_TOLERANCE) && Turret::pid->is_in_range(TURRET_TOLERANCE)) ||
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
        //memes

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

        set_point_entry = [](state* prev_state) -> void {
            Hood::pid->enable();
            Turret::pid->enable();
            Hood::pid->set_target(hood_set_point);
            Turret::pid->set_target(turret_set_point);
        };

        set_point->set_on_state_entry(set_point_entry);
        set_point->set_on_state_exit(std::function<void(state*)>([](state* next_state){}));

        auto_to_ready = []() -> bool {
            Vision::encoder_tuple auto_encoder_change = vision->get_encoder_setpoints();
            return abs(auto_encoder_change.altitude) + abs(auto_encoder_change.azimuth) < AUTO_TOLERANCE;
        };

        auto_aim->add_transition(std::function<bool()>([](){return !BaseReadable::operator_controller->is_digital_pressed(AUTO);}),manual);
//        auto_aim->add_transition(auto_to_ready,ready);

        hood_auto_target = []() -> double {
            if(!vision->has_target_rect()){
                vision->set_encoder_setpoints(Vision::encoder_tuple(
                    Turret::encoder->get_scaled_position() + BaseReadable::operator_controller->get_analog(TURRET_STICK),
                    Hood::encoder->get_position() + BaseReadable::operator_controller->get_analog(HOOD_STICK)
                    ));
            }
            double auto_hood_setpoint = vision->get_encoder_setpoints().altitude;
            if (auto_hood_setpoint > Hood::ENCODER_LIMIT) {
                return Hood::ENCODER_LIMIT;
            } else if (auto_hood_setpoint < 0) {
                return 0;
            } else {
                return auto_hood_setpoint;
            }
        };

        //meme

        turret_auto_target = []() -> double {
            if(!vision->has_target_rect()){
                vision->set_encoder_setpoints(Vision::encoder_tuple(
                    Turret::encoder->get_scaled_position() + BaseReadable::operator_controller->get_analog(TURRET_STICK),
                    Hood::encoder->get_position() + BaseReadable::operator_controller->get_analog(HOOD_STICK)
                    ));
            }
            double auto_turret_setpoint = vision->get_encoder_setpoints().azimuth;
            if (auto_turret_setpoint > Turret::ENCODER_LIMIT) {
                return Turret::ENCODER_LIMIT;
            } else if (auto_turret_setpoint < 0) {
                return 0;
            } else {
                return auto_turret_setpoint;
            }
        };

        vision->disable();
        auto_entry = [](state* prev_state) -> void {
            vision->enable();
            vision->set_encoder_setpoints(Vision::encoder_tuple(
                Turret::encoder->get_scaled_position(), 
                Hood::encoder->get_scaled_position()
            ));
            Hood::pid->enable();
            Hood::pid->reset_i_term();
            Turret::pid->enable();
            Turret::pid->reset_i_term();
            Hood::pid->set_target(hood_auto_target);
            Turret::pid->set_target(turret_auto_target);
            operator_rumble->set_operation(std::function<std::string()>([](){
                if(vision->has_target_rect()){
                    Vision::encoder_tuple auto_encoder_change = vision->get_encoder_setpoints();
                    if(vision->aiming_complete()){
                        if(Flywheel::pid_controller->is_in_range(50)){
                            return ".       ";
                        }
                        else{
                            return "-       ";
                        }
                    }
                    return "-       ";
                }
                else{
                    return "";
                }
            }),turret_state_controller->get_name());
        };

        auto_aim->set_on_state_entry(auto_entry);
        auto_aim->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Purging list" << std::endl;
            Hood::pid->disable();
            Turret::pid->disable();
            vision->purge_target_list();
            vision->disable();
            operator_rumble->set_value("",turret_state_controller->get_name());
        }));

        ready_to_auto = []() -> bool {
            return !(Hood::pid->is_in_range(HOOD_TOLERANCE) && Turret::pid->is_in_range(TURRET_TOLERANCE) && Flywheel::avg_speed->get_average_value() >= 0.95 * Flywheel::SPEED);
        };

        ready->add_transition(ready_to_auto,auto_aim);
        ready->add_transition(std::function<bool()>([](){return !BaseReadable::operator_controller->is_digital_pressed(AUTO);}),manual);

        ready_entry = [](state* prev_state) -> void {
            operator_rumble->set_value(".        ",turret_state_controller->get_name());
        };

        ready_exit = [](state* next_state) -> void {
            operator_rumble->set_value("",turret_state_controller->get_name());
        };

        ready->set_on_state_entry(ready_entry);
        ready->set_on_state_exit(ready_exit);

        zero_dick->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            Loader::motor->set_value(-12000,shooter_state_controller->get_name());
        }));
        zero_dick->set_on_state_exit(std::function<void(state*)>([](state* prev_state){
            Loader::encoder->tare_position();
            Loader::motor->set_operation(std::function<int16_t()>([](){
                return Loader::dead_band->get_deadband_value();
            }), shooter_state_controller->get_name());
        }));

        zero_dick->add_transition(std::function<bool()>([](){
            return Loader::motor->get_current() > 1300;
        }),manual);

        turret_state_controller->add_state(ready);
        turret_state_controller->add_state(auto_aim);
        turret_state_controller->add_state(set_point);
        turret_state_controller->add_state(zero_dick);
        turret_state_controller->set_state(zero_dick);
    }

    //memes

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