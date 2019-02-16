

#include "afr-vexu-lib/base-action/pid_action.h"
#include "afr-vexu-lib/base-action/set_value_action.h"
#include "afr-vexu-lib/base-readable/motor_encoder_readable.h"
#include "afr-vexu-lib/base-commandable/motor_commandable.h"
#include "afr-vexu-lib/base-readable/adi_analog_readable.h"
#include "afr-vexu-lib/base-action/dead_band_action.h"
#include "robot/robot.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "robot/shooter/shooter.h"
#include "robot/shooter/joystick.h"

namespace AFR::VexU::Robot::Shooter {
    BaseCommandable::motor_commandable *azimuth = nullptr;
    BaseCommandable::motor_commandable *flywheel = nullptr;
    joystick *start_azimuth = nullptr;

    BaseAction::dead_band_action<double, int16_t> *dead_band_azimuth = nullptr;
    BaseAction::pid_action<int16_t, int16_t> *flywheel_action = nullptr;
    BaseReadable::controller_digital_readable *azimuth_button = nullptr;
    BaseReadable::controller_digital_readable *flywheel_button = nullptr;
    //Action Map
    std::vector<action *> start_actions{};
    std::vector<action *> dummy_actions{};
    std::vector<action *> flywheel_actions{};
    std::function<bool()> dummy_to_start{};
    std::function<bool()> start_to_dummy{};

    std::function<bool()> flywheel_to_dummy{};
    std::function<bool()> dummy_to_flywheel{};
    //Transition vectors
    std::vector<transition> start_transitions{};
    std::vector<transition> dummy_transitions{};
    std::vector<transition> flywheel_transitions{};
    //On-state entry functions
    std::function<void(state *)> on_start_entry{};
    std::function<void(state *)> on_dummy_entry{};
    std::function<void(state *)> on_flywheel_entry{};
    //Readables
    BaseReadable::motor_encoder_readable *azimuth_encoder = nullptr;
    BaseReadable::motor_encoder_readable *flywheel_encoder = nullptr;
    //States
    state *dummy = nullptr;
    state *start = nullptr;
    state *flywheel_state = nullptr;
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

        azimuth_encoder = new motor_encoder_readable{AZIMUTH_PORT, 1.0, "azimuth_encoder"};
        // flywheel_encoder = new motor_encoder_readable{FLYWHEEL_PORT, 1.0, "flywheel_encoder"};

        azimuth_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, FIRE_BUTTON);
        //   flywheel_button = get_controller_digital_readable(pros::E_CONTROLLER_MASTER, SCORE_BUTTON);

        azimuth = new motor_commandable(AZIMUTH_PORT, AZIMUTH_MOTOR_GEARSET, true, AZIMUTH_MOTOR_BRAKE_MODE, "azimuth");
        left_stick = get_controller_analog_readable(pros::E_CONTROLLER_MASTER, LEFT_DRIVE_STICK);

        on_start_entry = [](state *last_state) -> void {};
        on_dummy_entry = [](state *last_state) -> void {};
        start_azimuth = new joystick{AZIMUTH_UPDATE_PERIOD, azimuth,
                                     left_stick, "start_azimuth", azimuth_encoder};

        start_transitions.emplace_back(start_to_dummy, dummy, "start_to_dummy");
        dummy_transitions.emplace_back(dummy_to_start, start, "dummy_to_start");

        dead_band_azimuth = new dead_band_action<double, int16_t>{AZIMUTH_UPDATE_PERIOD, azimuth, -90, 90,
                                                                  azimuth_encoder, -6000, 6000, "dead_band_azimuth"};
        flywheel_action = new pid_action<int16_t, int16_t>(FLYWHEEL_UPDATE_PERIOD, flywheel, 1, 1, 1, 0, 100, 0, 100, 0,
                                                           flywheel_encoder, 10, "flywheel");
        dummy_to_start = []() -> bool {
            return azimuth_button->is_pressed();
        };
        start_to_dummy = []() -> bool {
            return azimuth_encoder->get_position() >= AZIMUTH_THRESHOLD;
        };
        dummy_to_flywheel = []() -> bool {
            return flywheel_button->is_pressed();
        };
        flywheel_to_dummy = []() -> bool {
            return flywheel_encoder->get_position() >= FLYWHEEL_THRESHOLD;
        };
        start_actions.push_back(start_azimuth);
        flywheel_actions.push_back(flywheel_action);
        start = new state(start_actions, start_transitions, on_start_entry, "start");
        dummy = new state(dummy_actions, dummy_transitions, on_dummy_entry, "dummy");
        flywheel_state = new state(flywheel_actions, flywheel_transitions, on_flywheel_entry, "flywheel");
        states.push_back(start);
        states.push_back(dummy);
        states.push_back(flywheel_state);
        commandables.push_back(azimuth);

        shooter_state_machine = new state_controller(START_UPDATE_PERIOD, states, commandables, start,
                                                     "shooter_state_machine");

        state_machines.push_back(shooter_state_machine);
        shooter_subsystem = new subsystem_controller(inputs, state_machines, "shooter_subsystem");


    }

    void destroy() {
        delete (azimuth);


        delete (left_stick);


        delete (start);

        delete (shooter_state_machine);

        delete (shooter_subsystem);
    }


}