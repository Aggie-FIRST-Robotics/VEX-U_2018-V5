

#include "afr-vexu-lib/base-commandable/multi_motor_commandable.h"
#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "robot/robot.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/base-readable/motor_encoder_velocity_readable.h"


#include "robot/shooter/shooter.h"
#include "robot/shooter/joystick.h"

namespace AFR::VexU::Robot::Shooter {
    BaseCommandable::motor_commandable *elevation = nullptr;
    BaseCommandable::motor_commandable *flywheel = nullptr;
    BaseCommandable::motor_commandable *flywheel2 = nullptr;
    BaseCommandable::multi_motor_commandable *flywheel_combined = nullptr;
    BaseCommandable::motor_commandable *spinner = nullptr;
    joystick *start_elevation = nullptr;

    BaseAction::dead_band_action<double, int16_t> *dead_band_elevation = nullptr;
    BaseAction::dead_band_action<double, int16_t> *dead_band_spinner = nullptr;
    BaseAction::pid_action<double, int16_t> *flywheel_action = nullptr;

    BaseReadable::controller_digital_readable *flywheel_button = nullptr;
    //Action Map
    std::vector<action *> start_actions{};

    //Transition vectors
    std::vector<transition> start_transitions{};

    //On-state entry functions
    std::function<void(state *)> on_start_entry{};

    //Readables
    BaseReadable::motor_encoder_velocity_readable *elevation_encoder = nullptr;
    BaseReadable::motor_encoder_readable *spinner_encoder = nullptr;
    BaseReadable::motor_encoder_velocity_readable *flywheel_encoder = nullptr;

    //States

    state *start = nullptr;

    //state *joy = nullpr
    //State map
    std::vector<state *> states{};

    //Commandable map
    std::vector<commandable *> commandables{};

    //State controller
    state_controller *shooter_state_machine = nullptr;
    BaseReadable::controller_analog_readable *left_stick = nullptr;

    //Ordered input map
    std::vector<readable *> inputs{};

    //State controller map
    std::vector<state_controller *> state_machines{};

    subsystem_controller *shooter_subsystem = nullptr;


    void init() {
        using namespace BaseCommandable;
        using namespace BaseReadable;
        using namespace BaseAction;

        elevation_encoder = new motor_encoder_velocity_readable{ELEVATION_PORT, 1.0, "elevation_encoder"};
        spinner_encoder = new motor_encoder_readable{SPINNER_PORT, 1.0, "spinner_encoder"};

        flywheel_encoder = new motor_encoder_velocity_readable{FLYWHEEL_2_PORT, 1.0, "flywheel_encoder"};


        flywheel = new motor_commandable(FLYWHEEL_1_PORT, FLYWHEEL_MOTOR_GEARSET, true, FLYWHEEL_MOTOR_BRAKE_MODE,
                                         "flywheel");
        flywheel2 = new motor_commandable(FLYWHEEL_2_PORT, FLYWHEEL_MOTOR_GEARSET, false, FLYWHEEL_MOTOR_BRAKE_MODE,
                                          "flywheel");
        flywheel_combined = new multi_motor_commandable("flywheel_combined");
        flywheel_combined->add_motor(flywheel);
        flywheel_combined->add_motor(flywheel2);

        spinner = new motor_commandable(SPINNER_PORT, SPINNER_MOTOR_GEARSET, true, SPINNER_MOTOR_BRAKE_MODE, "spinner");
        elevation = new motor_commandable(ELEVATION_PORT, ELEVATION_MOTOR_GEARSET, true, ELEVATION_MOTOR_BRAKE_MODE,
                                          "elevation");
        left_stick = get_controller_analog_readable(pros::E_CONTROLLER_MASTER, LEFT_DRIVE_STICK);

        on_start_entry = [](state *last_state) -> void {};

        dead_band_elevation = new dead_band_action<double, int16_t>{ELEVATION_UPDATE_PERIOD, elevation, 0, 50,
                                                                    elevation_encoder, 3000, -3000,
                                                                    "dead_band_elevation"};
        flywheel_action = new pid_action<double, int16_t>(FLYWHEEL_UPDATE_PERIOD, flywheel_combined, 50, 30, 0, -12000,
                                                          12000, -12000, 12000, 0,
                                                          flywheel_encoder, 1000, "flywheel");
        dead_band_spinner = new dead_band_action<double, int16_t>{SPINNER_UPDATE_PERIOD, spinner, 500, 550,
                                                                  spinner_encoder, 6000, -6000, "dear_band_spinner"};

        start_elevation = new joystick(ELEVATION_UPDATE_PERIOD, elevation, left_stick, "start_elevation",
                                       elevation_encoder);

        start_actions.push_back(flywheel_action);

        start = new state(start_actions, start_transitions, on_start_entry, "start");


        //dummy = new state(dummy_actions, dummy_transitions, on_dummy_entry, "dummy");

        states.push_back(start);
        // states.push_back(dummy);

        commandables.push_back(elevation);
        commandables.push_back(flywheel);
        // std::cout<<"what is going on"<<std::endl;
        //  inputs.push_back(elevation_encoder);
        inputs.push_back(flywheel_encoder);
        /* commandables.push_back(spinner);*/
        shooter_state_machine = new state_controller(START_UPDATE_PERIOD, states, commandables, start,
                                                     "shooter_state_machine");

        state_machines.push_back(shooter_state_machine);
        shooter_subsystem = new subsystem_controller(inputs, state_machines, "shooter_subsystem");


    }

    void destroy() {
        delete (elevation);


        //  delete (left_stick);


        delete (start);

        delete (shooter_state_machine);

        delete (shooter_subsystem);
    }


}