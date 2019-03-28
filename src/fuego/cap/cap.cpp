#include "fuego/cap/cap.h"

namespace AFR::VexU::Fuego::Cap{

    struct cap_arm_meta{
        bool is_stealing;

        cap_arm_meta(){
            is_stealing = false;
        }

        explicit cap_arm_meta(bool is_stealing){
            this->is_stealing = is_stealing;
        };
    };

    /////State Controller
    state_controller<cap_arm_meta>* cap_arm = nullptr;

    /////States
    state* zero_arm = nullptr;
    state* zero_elbow = nullptr;
    state* store = nullptr;
    state* ground = nullptr;
    state* flip_low = nullptr;
    state* flip_high = nullptr;
    state* score_prime = nullptr;
    state* score = nullptr;
    state* descore_prime = nullptr;
    state* intake = nullptr;
    state* spit = nullptr;

    /////Edge detection for button lambdas
    BaseReadable::digital_edge_detector* elevate_button = nullptr;
    BaseReadable::digital_edge_detector* down_button = nullptr;
    BaseReadable::digital_edge_detector* descore_button = nullptr;
    BaseReadable::digital_edge_detector* flip_button = nullptr;
    BaseReadable::digital_edge_detector* reset_button = nullptr;

    void init(){
        //Readables
        cap_arm = new state_controller<cap_arm_meta>(UPDATE_PERIOD, cap_arm_meta{false},"cap arm state controller");

        Arm::init();
        Elbow::init();
        Wrist::init();

        zero_arm = new state("zero_shoulder");
        zero_elbow = new state("zero_elbow");
        store = new state("store");
        ground = new state("ground");
        flip_low = new state("flip low");
        flip_high = new state("flip high");
        score_prime = new state("score prime");
        score = new state("score");
        descore_prime = new state("descore prime");

        elevate_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, ELEVATE_BUTTON, "elevate button edge");
        down_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, DOWN_BUTTON, "ground button edge");
        descore_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, DESCORE_BUTTON, "steal button edge");
        flip_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, FLIP_BUTTON, "flip button edge");
        reset_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, RESET_BUTTON, "zero button edge");

        Arm::pid_controller->set_operation(std::function<double()>([](){
            return Arm::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Arm::left_motor->set_operation(std::function<double()>([](){
            return Arm::pid_controller->get_pid_value();
        }),cap_arm->get_name());
        Arm::right_motor->set_operation(std::function<double()>([](){
            return Elbow::pid_controller->get_pid_value();
        }),cap_arm->get_name());

        Elbow::pid_controller->set_operation(std::function<double()>([](){
            return Elbow::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Elbow::motor->set_operation(std::function<double()>([](){
            return Elbow::pid_controller->get_pid_value();
        }),cap_arm->get_name());

        Wrist::pid_controller->set_operation(std::function<double()>([](){
            return Wrist::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Wrist::flipping_motor->set_operation(std::function<double()>([](){
            return Wrist::pid_controller->get_pid_value();
        }),cap_arm->get_name());

        /////Zero Shoulder
            //////Transitions
            zero_arm->add_transition(std::function<bool()>([](){
                return Arm::zero_action->is_zeroed();
            }),zero_elbow);

            /////Entry/Exit Functions
            zero_arm->set_on_state_entry(std::function<void()>([](){
                Elbow::pid_controller->set_target(0);
                /////Run arm zero action
                Wrist::intake_motor->set_value(IDLE_VOLTAGE,cap_arm->get_name());
            }));
            zero_arm->set_on_state_exit(std::function<void()>([](){
                /////Stop arm zero action
            }));

        cap_arm->add_state(zero_arm);

        /////Zero Elbow
            /////Transitions
            zero_elbow->add_transition(std::function<bool()>([](){
                return Elbow::zero_action->is_zeroed();
            }),store);

            /////Entry/Exit Functions
            zero_elbow->set_on_state_entry(std::function<void()>([](){
                /////Run elbow zero action
                Arm::pid_controller->set_target(0);
            }));
            zero_elbow->set_on_state_exit(std::function<void()>([](){
                /////Stop arm zero action
            }));

        cap_arm->add_state(zero_elbow);

        /////Store state
            /////Transitions
            store->add_transition(std::function<bool()>([](){
                return reset_button->is_rising_edge();
            }),zero_arm);
            store->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge();
            }),ground);
            store->add_transition(std::function<bool()>([](){
                return flip_button->is_rising_edge();
            }),flip_high);
            store->add_transition(std::function<bool()>([](){
                cap_arm->metadata().is_stealing = descore_button->is_rising_edge();
                return cap_arm->metadata().is_stealing;
            }),descore_prime);
            store->add_transition(std::function<bool()>([](){
                return elevate_button->is_rising_edge();
            }),score);

            /////Entry and exit functions
            store->set_on_state_entry(std::function<void()>([](){
                Arm::pid_controller->set_target(0);
                Elbow::pid_controller->set_target(ELBOW_STORE_POSITION);
                Wrist::intake_motor->set_value(IDLE_VOLTAGE,cap_arm->get_name());
            }));
            store->set_on_state_exit(std::function<void()>([](){

            }));

        cap_arm->add_state(store);

        /////Ground state
            /////Transitions
            ground->add_transition(std::function<bool()>([](){
                return elevate_button->is_rising_edge();
            }),store);
            ground->add_transition(std::function<bool()>([](){
                return flip_button->is_rising_edge();
            }),flip_low);
            ground->add_transition(std::function<bool()>([](){
                return reset_button->is_rising_edge();
            }),zero_arm);
            ground->add_transition(std::function<bool()>([](){
                return BaseReadable::driver_controller->is_digital_pressed(INTAKE_BUTTON);
            }),intake);
            ground->add_transition(std::function<bool()>([](){
                return BaseReadable::driver_controller->is_digital_pressed(OUTTAKE_BUTTON);
            }),spit);

            /////Entry/Exit Functions
            ground->set_on_state_entry(std::function<void()>([](){
                Arm::pid_controller->set_target(ARM_GROUND_POSITION);
                Elbow::pid_controller->set_target(ELBOW_GROUND_POSITION);
            }));
            ground->set_on_state_exit(std::function<void()>([](){

            }));

        /////Intake State
            /////Transtions
            intake->add_transition(std::function<bool()>([](){
                return !BaseReadable::driver_controller->is_digital_pressed(INTAKE_BUTTON);
            }),ground);

            /////Entry/Exit Function
            intake->set_on_state_entry(std::function<void()>([](){
                Wrist::intake_motor->set_value(INTAKE_VOLTAGE,cap_arm->get_name());
            }));
            intake->set_on_state_exit(std::function<void()>([](){
                Wrist::intake_motor->set_value(IDLE_VOLTAGE,cap_arm->get_name());
            }));

        /////Spit State
            /////Transtions
            spit->add_transition(std::function<bool()>([](){
                return !BaseReadable::driver_controller->is_digital_pressed(OUTTAKE_BUTTON);
            }),ground);

            /////Entry/Exit Function
            spit->set_on_state_entry(std::function<void()>([](){
                Wrist::intake_motor->set_value(-INTAKE_VOLTAGE,cap_arm->get_name());
            }));
            spit->set_on_state_exit(std::function<void()>([](){
                Wrist::intake_motor->set_value(IDLE_VOLTAGE,cap_arm->get_name());
            }));

        /////Flip Low State
            /////Transitions
            flip_low->add_transition(std::function<bool()>([](){
                /////Did the wrist flip
                return true;
            }),ground);

            /////Entry/Exit Functions
            flip_low->set_on_state_entry(std::function<void()>([](){
                Elbow::pid_controller->set_target(ELBOW_FLIP_LOW_POSITION);
            }));
            flip_low->set_on_state_exit(std::function<void()>([](){

            }));

        /////Flip High State
            /////Transitions
            flip_high->add_transition(std::function<bool()>([](){
                /////Did the wrist flip
                return true;
            }),store);

            /////Entry/Exit Functions
            flip_high->set_on_state_entry(std::function<void()>([](){
                Elbow::pid_controller->set_target(ELBOW_FLIP_HIGH_POSITION);
            }));
            flip_high->set_on_state_exit(std::function<void()>([](){

            }));

        /////Score Prime State
            /////Transitions
            score_prime->add_transition(std::function<bool()>([](){
                if(cap_arm->metadata().is_stealing){
                    /////Did the wrist flip action occur
                    cap_arm->metadata().is_stealing = false;
                    return true;
                }
                else {
                    return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && BaseReadable::operator_controller->is_digital_pressed(ELEVATE_BUTTON);
                }
            }),score);
            score_prime->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge();
            }),zero_arm);

            /////Entry/Exit Functions
            score_prime->set_on_state_entry(std::function<void()>([](){
                Arm::pid_controller->set_target(ARM_SCORE_PRIME_POSITION);
                Elbow::pid_controller->set_target(ELBOW_SCORE_PRIME_POSITION);
                Wrist::intake_motor->set_value(IDLE_VOLTAGE, cap_arm->get_name());
                if(cap_arm->metadata().is_stealing) {
                    /////Run wrist flip action
                }
            }));
            score_prime->set_on_state_exit(std::function<void()>([](){

            }));

        ////Score State
            /////Transitions
            score->add_transition(std::function<bool()>([](){
                return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && cap_arm->metadata().is_stealing;
            }),score_prime);
            score->add_transition(std::function<bool()>([](){
                return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && !cap_arm->metadata().is_stealing;
            }),descore_prime);

            /////Entry/Exit Functions
            score->set_on_state_entry(std::function<void()>([](){
                Arm::pid_controller->set_target(ARM_SCORE_POSITION);
                Elbow::pid_controller->set_target(ELBOW_SCORE_POSITION);
                if(cap_arm->metadata().is_stealing){
                    Wrist::intake_motor->set_value(INTAKE_VOLTAGE,cap_arm->get_name());
                }
            }));
            score->set_on_state_exit(std::function<void()>([](){

            }));

        ////Descore Prime State
            /////Transitions
            descore_prime->add_transition(std::function<bool()>([](){
                return cap_arm->metadata().is_stealing && down_button->is_rising_edge();
            }),store);
            descore_prime->add_transition(std::function<bool()>([](){
                return cap_arm->metadata().is_stealing && down_button->is_rising_edge();
                if(cap_arm->metadata().is_stealing){

                }
                else{

                }
            }),zero_arm);
            descore_prime->add_transition(std::function<bool()>([](){
                return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && cap_arm->metadata().is_stealing;
            }),score);

            /////Entry/Exit Functions
            descore_prime->set_on_state_entry(std::function<void()>([](){
                Arm::pid_controller->set_target(ARM_DESCORE_PRIME_POSITION);
                Elbow::pid_controller->set_target(ELBOW_DESCORE_PRIME_POSITION);
                if(!cap_arm->metadata().is_stealing){
                    Wrist::intake_motor->set_value(-INTAKE_VOLTAGE,cap_arm->get_name());
                }
            }));
            descore_prime->set_on_state_exit(std::function<void()>([](){

            }));


    }
}
