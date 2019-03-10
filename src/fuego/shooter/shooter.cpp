

#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "fuego/shooter/shooter.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"
#include "afr-vexu-lib/base-action/bounded_value_action.h"



namespace AFR::VexU::Fuego::Shooter{
    scheduled_update_t next_loader = 0;
    scheduled_update_t next_auto_aim = 0;


    /////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* shooter_state_controller{};

    //Shooter wheel is inactive
    state* rest{};
    std::vector<std::pair<std::function<bool()>, state*>> rest_transitions;
    std::function<void()> rest_entry;
    std::function<void()> rest_exit;

        commandable<int16_t>

    //Shooter wheel is spinning up
    state* spin_up{};
    std::vector<std::pair<std::function<bool()>, state*>> spin_up_transitions;
    std::function<void()> spin_up_entry;
    std::function<void()> spin_up_exit;

    /////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* loader_state_controller{};

    //Loader is holding position at ready
    state* cock{};
    std::vector<std::pair<std::function<bool()>, state*>> cock_transitions;
    std::function<void()> cock_entry;
    std::function<void()> cock_exit;

    //Loader goes to the high position, fires ball
    state* fire{};
    std::vector<std::pair<std::function<bool()>, state*>> fire_transitions;
    std::function<void()> fire_entry;
    std::function<void()> fire_exit;

    //Loader goes to low position, lifts robot
    state* walk{};
    std::vector<std::pair<std::function<bool()>, state*>> walk_transitions;
    std::function<void()> walk_entry;
    std::function<void()> walk_exit;

    /////////////////////////////////////////////////////////////////////////////////////////////

    state_controller<void>* auto_aim_state_controller{};

    //Operate shooter in manual mode via control sticks
    state* manual{};
    std::vector<std::pair<std::function<bool()>, state*>> manual_transitions;
    std::function<void()> manual_entry;
    std::function<void()> manual_exit;

    //Shooter searches for target
    state* auto_aim{};
    std::vector<std::pair<std::function<bool()>, state*>> auto_aim_transitions;
    std::function<void()> auto_aim_entry;
    std::function<void()> auto_aim_exit;

    //Shooter is locked onto a target
    state* ready{};
    std::vector<std::pair<std::function<bool()>, state*>> ready_transitions;
    std::function<void()> ready_entry;
    std::function<void()> ready_exit;

    /////////////////////////////////////////////////////////////////////////////////////////////

    BaseAction::bounded_value_action< double, int32_t ,int16_t >* follow_stick_hood = nullptr;

    //Readable functions
    std::function<int32_t()> get_stick_x{};
    std::function<int32_t()> get_stick_y{};

    std::function<double()> get_hood_encoder{};
    std::function<double()> get_turret_encoder{};
    std::function<double()> get_loader_encoder{};


    //Commandables
    BaseCommandable::motor_commandable*         loader_motor_1 = nullptr;
    BaseCommandable::motor_commandable*         loader_motor_2 = nullptr;
    BaseCommandable::motor_commandable*         hood_motor = nullptr;
    BaseAction::dead_band_action*         turret_motor = nullptr;
    BaseCommandable::motor_commandable*         flywheel_left = nullptr;
    BaseCommandable::motor_commandable*         flywheel_right = nullptr;
    BaseCommandable::multi_motor_commandable*   flywheel_motors = nullptr;
    BaseCommandable::multi_motor_commandable*   loader_motors = nullptr;

    //Readables
    BaseReadable::motor_encoder_readable*           hood_encoder = nullptr;
    BaseReadable::motor_encoder_readable*           turret_encoder = nullptr;
    BaseReadable::motor_encoder_velocity_readable*  flywheel_velocity = nullptr;
    BaseReadable::controller_digital_readable*      auto_aim_button = nullptr;
    BaseReadable::controller_digital_readable*      spin_up_button = nullptr;
    BaseReadable::controller_digital_readable*      fire_button = nullptr;
    BaseReadable::controller_analog_readable*       vertical_stick = nullptr;
    BaseReadable::controller_analog_readable*       horizontal_stick = nullptr;

    //Actions
    BaseAction::set_value_action<int16_t>*  loader_cock_action = nullptr;
    BaseAction::set_value_action<int16_t>*  loader_fire_action = nullptr;
    BaseAction::set_value_action<int16_t>*  loader_rest_action = nullptr;
    BaseAction::set_value_action<int16_t>*  hood_lock_action = nullptr;
    BaseAction::set_value_action<int16_t>*  turret_lock_action = nullptr;
    BaseAction::set_value_action<int16_t>*  flywheel_left_rest_action = nullptr;
    BaseAction::set_value_action<int16_t>*  flywheel_right_rest_action = nullptr;

    BaseAction::dead_band_action<double, int16_t>*  hood_dead_band_action = nullptr;
    BaseAction::dead_band_action<double, int16_t>*  turret_dead_band_action = nullptr;

    BaseAction::pid_action<double, int16_t>*    flywheel_pid_action = nullptr;

    BaseAction::bounded_value_action<double,int32_t ,int16_t >* hood_value_bound_action = nullptr;
    BaseAction::bounded_value_action<double,int32_t ,int16_t >* turret_value_bound_action = nullptr;


    //Firing Action Vectors
    std::vector<action*> rest_actions{};
    std::vector<action*> spin_up_actions{};
    std::vector<action*> cock_actions{};
    std::vector<action*> fire_actions{};

    //Autoaim Action Vectors
    std::vector<action*> manual_control_actions{};
    std::vector<action*> auto_aim_actions{};
    std::vector<action*> ready_actions{};


    //Firing Transition Functions
    std::function<bool()> rest_to_spin_up{};

    std::function<bool()> spin_up_to_rest{};
    std::function<bool()> spin_up_to_cock{};

    std::function<bool()> cock_to_fire{};

    std::function<bool()> fire_to_spin_up{};
    std::function<bool()> fire_to_rest{};

    //Autoaim Transition Functions
    std::function<bool()> manual_to_auto{};

    std::function<bool()> auto_to_manual{};
    std::function<bool()> auto_to_ready{};

    std::function<bool()> ready_to_auto{};
    std::function<bool()> ready_to_manual{};


    //Firing Transition Vectors
    std::vector<transition> rest_transitions{};
    std::vector<transition> spin_up_transitions{};
    std::vector<transition> cock_transitions{};
    std::vector<transition> fire_transitions{};

    //Autoaim Transistion Vectors
    std::vector<transition> manual_transitions{};
    std::vector<transition> auto_transitions{};
    std::vector<transition> ready_transitions{};


    //Firing On State Entry Functions
    std::function<void(state*)> on_rest_entry{};
    std::function<void(state*)> on_spin_up_entry{};
    std::function<void(state*)> on_cock_entry{};
    std::function<void(state*)> on_fire_entry{};

    //Autoaim On State Entry Functions
    std::function<void(state*)> on_manual_entry{};
    std::function<void(state*)> on_auto_entry{};
    std::function<void(state*)> on_ready_entry{};


    //Firing States
    state* rest{};
    state* spin_up{};
    state* cock{};
    state* fire{};


    //Autoaim States
    state* manual{};
    state* autoaim{};
    state* ready{};


    //State Vector
    std::vector<state*> firing_states{};
    std::vector<state*> autoaim_states{};

    //Commandable Vector
    std::vector<commandable*> firing_commandables{};
    std::vector<commandable*> autoaim_commandables{};

    //State Controller
    state_controller* firing_state_machine{};
    state_controller* autoaim_state_machine{};

    //Readable Vector
    std::vector<readable*> readables{};

    //State Controller Vector
    std::vector<state_controller*> state_controllers{};

    //Subsystem Controller
    subsystem_controller* shooter_subsystem{};

    //Conversion Functions
    std::function<int16_t(int32_t)> shooter_bounding{};


    void init(){
        shooter_state_controller = new state_controller<void>{SHOOTER_UPDATE_PERIOD,"shooter_state_machine"};
        auto_aim_state_controller = new state_controller<void>{AUTO_AIM_UPDATE_PERIOD,"auto_aim_state_machine"};


//        autoaim_state_controller = new state_controller<void>{10,"autoaim_state_machine"};

//        using namespace BaseCommandable;
//        using namespace BaseReadable;
//        using namespace BaseAction;
//
//        shooter_bounding = [](int32_t input) -> int16_t{
//            return static_cast<int16_t>((12000 / 127) * input);
//        };
//
//        //Commandables
//        loader_motor_1       = new motor_commandable{LOADER_MOTOR_PORT_1, LOADER_MOTOR_GEARSET, true, LOADER_MOTOR_BRAKE_MODE, "loader_motor"};
//        loader_motor_2       = new motor_commandable{LOADER_MOTOR_PORT_2, LOADER_MOTOR_GEARSET, false, LOADER_MOTOR_BRAKE_MODE, "loader_motor"};
//        loader_motors     = new multi_motor_commandable{"loader_motors"};
//        loader_motors->add_motor(loader_motor_1);
//        loader_motors->add_motor(loader_motor_2);
//
//        hood_motor          = new motor_commandable{HOOD_MOTOR_PORT, HOOD_MOTOR_GEARSET, true, HOOD_MOTOR_BRAKE_MODE, "hood_motor"};
//        turret_motor        = new motor_commandable{TURRET_MOTOR_PORT, TURRET_MOTOR_GEARSET, false, TURRET_MOTOR_BRAKE_MODE, "turret_motor"};
//
//        flywheel_left       = new motor_commandable{FLYWHEEL_LEFT_PORT, FLYWHEEL_LEFT_GEARSET, false, FLYWHEEL_LEFT_BRAKE_MODE, "flywheel_left_motor"};
//        flywheel_right      = new motor_commandable{FLYWHEEL_RIGHT_PORT, FLYWHEEL_RIGHT_GEARSET, true, FLYWHEEL_RIGHT_BRAKE_MODE, "flywheel_right_motor"};
//        flywheel_motors     = new multi_motor_commandable{"flywheel_motors"};
//        flywheel_motors->add_motor(flywheel_left);
//        flywheel_motors->add_motor(flywheel_right);
//
//
//        //Readabl
//        hood_encoder            = new motor_encoder_readable{HOOD_MOTOR_PORT, HOOD_ENCODER_SCALING, "hood_motor_encoder"};
//        turret_encoder          = new motor_encoder_readable{TURRET_MOTOR_PORT, TURRET_ENCODER_SCALING, "turret_motor_encoder"};
//        flywheel_velocity       = new motor_encoder_velocity_readable{FLYWHEEL_LEFT_PORT, 1.0, "flywheel_velocity"};
//
//        auto_aim_button = get_controller_digital_readable(pros::E_CONTROLLER_PARTNER, AUTO_AIM_BUTTON);
//        spin_up_button = get_controller_digital_readable(pros::E_CONTROLLER_PARTNER, SPIN_UP_BUTTON);
//        fire_button = get_controller_digital_readable(pros::E_CONTROLLER_PARTNER, FIRE_BUTTON);
//
//        vertical_stick = get_controller_analog_readable(pros::E_CONTROLLER_PARTNER, VERTICAL_STICK);
//        horizontal_stick = get_controller_analog_readable(pros::E_CONTROLLER_PARTNER, HORIZONTAL_STICK);
//
//        //Actions
//        loader_cock_action = new set_value_action<int16_t>{LOADER_UPDATE_PERIOD, loader_motors, 12000, "loader_cock_action"};
//        loader_fire_action = new set_value_action<int16_t>{LOADER_UPDATE_PERIOD, loader_motors, -12000, "loader_fire_action"};
//        loader_rest_action = new set_value_action<int16_t>{LOADER_UPDATE_PERIOD, loader_motors, 0, "loader_rest_action"};
//        hood_lock_action = new set_value_action<int16_t>{AUTO_AIM_UPDATE_PERIOD, hood_motor, 0, "hood_lock_action"};
//        turret_lock_action = new set_value_action<int16_t>{AUTO_AIM_UPDATE_PERIOD, turret_motor, 0, "turret_lock_action"};
//        flywheel_left_rest_action = new set_value_action<int16_t>{SHOOTER_UPDATE_PERIOD, flywheel_left, 0, "flywheel_left_rest_action"};
//        flywheel_right_rest_action = new set_value_action<int16_t>{SHOOTER_UPDATE_PERIOD, flywheel_right, 0, "flywheel_right_rest_action"};
//        hood_dead_band_action = new dead_band_action<double, int16_t>{AUTO_AIM_UPDATE_PERIOD, hood_motor, hood_encoder->get_position()-HOOD_TOLERANCE, hood_encoder->get_position() + HOOD_TOLERANCE, hood_encoder, HOOD_VOLTAGE, -HOOD_VOLTAGE, "hood_dead_band_action"};
//        turret_dead_band_action = new dead_band_action<double, int16_t>{AUTO_AIM_UPDATE_PERIOD, turret_motor, turret_encoder->get_position()-TURRET_TOLERANCE, turret_encoder->get_position() + TURRET_TOLERANCE, turret_encoder, TURRET_VOLTAGE, -TURRET_VOLTAGE, "turret_dead_band_action"};
//        flywheel_pid_action = new pid_action<double, int16_t>{SHOOTER_UPDATE_PERIOD, flywheel_motors, P_TERM, I_TERM, D_TERM, -12000, 12000, MIN_I_TERM, MAX_I_TERM, 0, flywheel_velocity, FLYWHEEL_SPEED, "flywheel_pid_action"};
//        hood_value_bound_action = new bounded_value_action<double,int32_t ,int16_t >(AUTO_AIM_UPDATE_PERIOD, hood_motor, HOOD_ENCODER_LIMIT, 0, 0, 0, shooter_bounding, vertical_stick,  hood_encoder, "bounded_hood_action");
        turret_value_bound_action = new bounded_value_action<double,int32_t ,int16_t >(AUTO_AIM_UPDATE_PERIOD, turret_motor, TURRET_ENCODER_LIMIT, 0, 0, 0, shooter_bounding, horizontal_stick,  turret_encoder, "bounded_turret_action");
//        //Firing Vectors
//        rest_actions.push_back(flywheel_left_rest_action);
//        rest_actions.push_back(flywheel_right_rest_action);
//        rest_actions.push_back(loader_rest_action);
//
//        spin_up_actions.push_back(flywheel_pid_action);
//        spin_up_actions.push_back(loader_rest_action);
//
//        cock_actions.push_back(flywheel_pid_action);
//        cock_actions.push_back(loader_cock_action);
//
//        fire_actions.push_back(flywheel_pid_action);
//        fire_actions.push_back(loader_fire_action);
//
//
//        //Autoaim Vectors
//        manual_control_actions.push_back(hood_value_bound_action);
//        manual_control_actions.push_back(turret_value_bound_action);
//
//        auto_aim_actions.push_back(hood_dead_band_action);
//        auto_aim_actions.push_back(turret_dead_band_action);
//
//        ready_actions.push_back(hood_lock_action);
//        ready_actions.push_back(turret_lock_action);
//
//
//        //Firing Transition Functions
//        rest_to_spin_up = []() -> bool{
//            return spin_up_button->is_pressed();
//        };
//
//        spin_up_to_rest = []() -> bool{
//            return !spin_up_button->is_pressed();
//        };
//        spin_up_to_cock = []() -> bool{
//            return fire_button->is_rising_edge() && flywheel_pid_action->is_in_range(FLYWHEEL_TOLERANCE);
//        };
//
//        cock_to_fire = []() -> bool{
//            return next_loader <= pros::millis();
//        };
//
//        fire_to_spin_up = []() -> bool{
//            return next_loader <= pros::millis();
//        };
//
//
//        //Autoaim Transitian Functions
//        manual_to_auto = []() -> bool{
//            return auto_aim_button->is_pressed();
//        };
//
//        auto_to_manual = []() -> bool{
//            return !auto_aim_button->is_pressed();
//        };
//
//        auto_to_ready = []() -> bool{
//            return hood_dead_band_action->is_in_range(HOOD_TOLERANCE) && turret_dead_band_action->is_in_range(TURRET_TOLERANCE);
//        };
//
//        ready_to_auto = []() -> bool{
//            return auto_aim_button->is_pressed() && next_auto_aim <= pros::millis();
//        };
//
//        ready_to_manual = []() -> bool{
//            return next_auto_aim <= pros::millis();
//        };
//
//        //Firing Transition Vectors
//        rest_transitions.emplace_back(rest_to_spin_up, spin_up, "rest_to_spin_up");
//
//        spin_up_transitions.emplace_back(spin_up_to_rest, rest, "spin_up_to_rest");
//        spin_up_transitions.emplace_back(spin_up_to_cock, cock, "spin_up_to_cock");
//
//        cock_transitions.emplace_back(cock_to_fire, fire, "cock_to_fire");
//
//        fire_transitions.emplace_back(fire_to_spin_up, spin_up, "fire_to_spin_up");
//        fire_transitions.emplace_back(fire_to_rest, rest, "fire_to_rest");
//
//        //Autoaim Transistion Vectors
//        manual_transitions.emplace_back(manual_to_auto, autoaim, "manual_to_auto");
//
//        auto_transitions.emplace_back(auto_to_manual, manual, "auto_to_manual");
//        auto_transitions.emplace_back(auto_to_ready, ready, "auto_to_ready");
//
//        ready_transitions.emplace_back(ready_to_auto, autoaim, "ready_to_autoaim");
//        ready_transitions.emplace_back(ready_to_manual, manual, "ready_to_manual");
//
//        //Firing On State Entry Functions
//        on_rest_entry = [](state* last_state) -> void{
//            flywheel_pid_action->disable();
//        };
//        on_spin_up_entry = [](state* last_state) -> void{
//            flywheel_pid_action->set_target(FLYWHEEL_SPEED);
//        };
//        on_cock_entry = [](state* last_state) -> void{
//            next_loader = pros::millis() + LOADER_STOP_TIME;
//            flywheel_pid_action->set_target(FLYWHEEL_SPEED);
//        };
//        on_fire_entry = [](state* last_state) -> void{
//            next_loader = pros::millis() + LOADER_STOP_TIME;
//            flywheel_pid_action->set_target(FLYWHEEL_SPEED);
//        };
//        //Autoaim On State Entry Functions
//        on_manual_entry = [](state* last_state) -> void{};
//        on_auto_entry = [](state* last_state) -> void{
//            //if(/*encoder target*/ > 0 && /*encoder target*/ < HOOD_ENCODER_LIMIT)
//                //hood_dead_band_action.set_target(/*encoder target*/);
//            //if(/*encoder target*/ > 0 && /*encoder target*/ < TURRET_ENCODER_LIMIT)
//                //turret_dead_band_action.set_target(/*delta encoder counts*/);
//        };
//        on_ready_entry = [](state* last_state) -> void{
//            next_auto_aim = pros::millis() + AUTO_AIM_DELAY;
//        };
//
//        //Firing States
//        rest = new state{rest_actions, rest_transitions, on_rest_entry, "rest"};
//        spin_up = new state{spin_up_actions, spin_up_transitions, on_spin_up_entry, "spin_up"};
//        cock = new state{cock_actions, cock_transitions, on_cock_entry, "cock"};
//        fire = new state{fire_actions, fire_transitions, on_fire_entry, "fire"};
//
//        //Autoaim States
//        manual = new state{manual_control_actions, manual_transitions, on_manual_entry, "manual"};
//        autoaim = new state{auto_aim_actions, auto_transitions, on_auto_entry, "auto"};
//        ready = new state{ready_actions, ready_transitions, on_ready_entry, "ready"};
//
//
//        //Firing State Vector
//        firing_states.push_back(rest);
        firing_states.push_back(spin_up);
        firing_states.push_back(cock);
        firing_states.push_back(fire);


        //Autoaim State Vector
        autoaim_states.push_back(manual);
        autoaim_states.push_back(autoaim);
        autoaim_states.push_back(ready);


        //Firing Commandable Vector
        firing_commandables.push_back(loader_motors);
        firing_commandables.push_back(flywheel_left);
        firing_commandables.push_back(flywheel_right);
        firing_commandables.push_back(flywheel_motors);


        //Autoaim Commandable Vector
        autoaim_commandables.push_back(hood_motor);
        autoaim_commandables.push_back(turret_motor);

        //State Controllers
        firing_state_machine = new state_controller{SHOOTER_UPDATE_PERIOD, firing_states, firing_commandables, rest, "firing_state_machine"};
        autoaim_state_machine = new state_controller{AUTO_AIM_UPDATE_PERIOD, autoaim_states, autoaim_commandables, manual, "autoaim_state_machine"};

        //Readable Vector
        readables.push_back(hood_encoder);
        readables.push_back(turret_encoder);
        readables.push_back(flywheel_velocity);
        readables.push_back(auto_aim_button);
        readables.push_back(spin_up_button);
        readables.push_back(fire_button);
        readables.push_back(vertical_stick);
        readables.push_back(horizontal_stick);


        //State Controller Vector
        state_controllers.push_back(firing_state_machine);
        state_controllers.push_back(autoaim_state_machine);



    }

    void destroy(){
        delete loader_motor_1;
        delete loader_motor_2;
        delete loader_motors;
        delete hood_motor;
        delete turret_motor;
        delete flywheel_left;
        delete flywheel_right;
        delete flywheel_motors;
        delete hood_encoder;
        delete turret_encoder;
        delete flywheel_velocity;
        delete loader_cock_action;
        delete loader_fire_action;
        delete loader_rest_action;
        delete flywheel_left_rest_action;
        delete flywheel_right_rest_action;
        delete hood_dead_band_action;
        delete turret_dead_band_action;
        delete flywheel_pid_action;
        delete hood_value_bound_action;
        delete turret_dead_band_action;
        delete rest;
        delete spin_up;
        delete cock;
        delete fire;
        delete manual;
        delete autoaim;
        delete ready;
        delete firing_state_machine;
        delete autoaim_state_machine;
        delete shooter_subsystem;
    }


}