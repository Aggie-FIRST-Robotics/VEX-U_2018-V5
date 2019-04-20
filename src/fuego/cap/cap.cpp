#include "fuego/cap/cap.h"

namespace AFR::VexU::Fuego::Cap{
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
    state* score_flip = nullptr;
    state* score = nullptr;
    state* descore_prime = nullptr;
    state* dick = nullptr;
    state* ascend_prime = nullptr;
    state* ascend = nullptr;
    state* angled_pickup = nullptr;
    state* ball_prime = nullptr;
    state* ball_sweep = nullptr;

    /////Edge detection for button lambdas
    BaseReadable::digital_edge_detector* elevate_button = nullptr;
    BaseReadable::digital_edge_detector* down_button = nullptr;
    BaseReadable::digital_edge_detector* descore_button = nullptr;
    BaseReadable::digital_edge_detector* flip_button = nullptr;
    BaseReadable::digital_edge_detector* reset_button = nullptr;
    BaseReadable::digital_edge_detector* dick_button = nullptr;

    std::function<int16_t()> idle_intake_function = []() -> int16_t{
        if(BaseReadable::driver_controller->is_digital_pressed(INTAKE_BUTTON)){
            return INTAKE_VOLTAGE;
        }
        else if(BaseReadable::driver_controller->is_digital_pressed(OUTTAKE_BUTTON)){
            return -INTAKE_VOLTAGE;
        }
        else{
            return IDLE_VOLTAGE;
        }
    };

    std::function<int16_t()> zero_arm_action;
    std::function<int16_t()> zero_elbow_action;
    std::function<int16_t()> zero_wrist_action;
    std::function<double()> wrist_flip_target;

    void init(){
        cap_arm = new state_controller<cap_arm_meta>(UPDATE_PERIOD, cap_arm_meta{false},"cap arm state controller");

        Arm::init();
        Elbow::init();
        Wrist::init();

        zero_arm = new state("zero_shoulder");
        zero_elbow = new state("zero_elbow");
        store = new state("store");
        ground = new state("ground");
        flip_low = new state("flip_low");
        flip_high = new state("flip_high");
        score_prime = new state("score_prime");
        score_flip = new state("score_flip");
        score = new state("score");
        descore_prime = new state("descore_prime");
        dick = new state("dick");
        ascend_prime = new state("ascend_prime");
        ascend = new state("ascend");
        angled_pickup = new state("angled_pickup");
        ball_prime = new state("ball_prime");
        ball_sweep = new state("ball_sweep");

        elevate_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, ELEVATE_BUTTON, "elevate button edge");
        down_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, DOWN_BUTTON, "ground button edge");
        descore_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, DESCORE_BUTTON, "steal button edge");
        flip_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, FLIP_BUTTON, "flip button edge");
        reset_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, RESET_BUTTON, "zero button edge");
        dick_button = new BaseReadable::digital_edge_detector(CONTROLLER_MASTER, WALK, "dick button edge");

        zero_arm_action = []() -> int16_t{ 
            if(Arm::limit_switch->is_pressed()){
                return -200;
            }
            else{
                return -12000;
            }
        };

        zero_elbow_action = []() -> int16_t{
            if(Elbow::limit_switch->is_pressed()){
                return 0;
            }
            else{
                return -12000;
            }
        };

        zero_wrist_action = []() -> int16_t{ 
            if(Wrist::limit_switch->is_pressed()){
                return -200;
            }
            else{
                return -12000;
            }
        };

        wrist_flip_target = []() -> double{ 
            if(Wrist::pid_controller->get_last_target() == 0){
                return WRIST_FLIP_POSITION;
            }
            else {
                return 0;
            }
        };

        Arm::pid_controller->set_operation(std::function<double()>([](){
            return Arm::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Arm::left_motor->set_operation(zero_arm_action,cap_arm->get_name());
        Arm::right_motor->set_operation(zero_arm_action,cap_arm->get_name());


        Elbow::pid_controller->set_operation(std::function<double()>([](){
            return Elbow::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Elbow::motor->set_operation(std::function<int16_t()>([](){
            // std::cout << "Elbow: " << Elbow::encoder->get_scaled_position() << std::endl;
            // return 0;
            return Elbow::pid_controller->get_pid_value();
        }),cap_arm->get_name());


        Wrist::pid_controller->set_operation(std::function<double()>([](){
            // std::cout << Wrist::encoder->get_scaled_position() << std::endl;
            return Wrist::encoder->get_scaled_position();
        }),cap_arm->get_name());
        Wrist::flipping_motor->set_operation(zero_wrist_action,cap_arm->get_name());
        Wrist::intake_motor->set_operation(idle_intake_function,cap_arm->get_name());

        /////Zero Shoulder
            //////Transitions
            zero_arm->add_transition(std::function<bool()>([](){
                if (Arm::debounce->is_triggered()) {
                    Arm::encoder->tare_position();
                    // Wrist::encoder->tare_position();
                    return true;
                }
                return false;
            }),zero_elbow);

            /////Entry/Exit Functions
            zero_arm->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                std::cout << "Zero Arm Entry" << std::endl;
                Elbow::pid_controller->set_target(0);
                Arm::left_motor->set_operation(zero_arm_action,cap_arm->get_name());
                Arm::right_motor->set_operation(zero_arm_action,cap_arm->get_name());
                Wrist::flipping_motor->set_operation(zero_wrist_action, cap_arm->get_name());
            }));
            zero_arm->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                std::cout << "Zero Arm Exit" << std::endl;
                Wrist::pid_controller->set_target(0);
                Arm::pid_controller->set_target(-30);
                Arm::left_motor->set_operation(std::function<int16_t()>([](){
                    return Arm::pid_controller->get_pid_value();
                }),cap_arm->get_name());
                Arm::right_motor->set_operation(std::function<int16_t()>([](){
                    return Arm::pid_controller->get_pid_value();
                }),cap_arm->get_name());
                Wrist::flipping_motor->set_operation(std::function<int16_t()>([](){
                    return Wrist::pid_controller->get_pid_value();
                }), cap_arm->get_name());
            }));

        /////Zero Elbow
            /////Transitions
            zero_elbow->add_transition(std::function<bool()>([](){
                if(Elbow::debounce->is_triggered()){
                    Elbow::encoder->tare_position();
                    return true;
                }
                return false;
            }),store);

            /////Entry/Exit Functions
            zero_elbow->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                std::cout << "Zero Elbow Entry" << std::endl;
                Elbow::motor->set_operation(zero_elbow_action,cap_arm->get_name());
            }));
            zero_elbow->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                std::cout << "Zero Elbow Exit" << std::endl;
                Elbow::motor->set_operation(std::function<int16_t()>([](){
                    return Elbow::pid_controller->get_pid_value();
                }),cap_arm->get_name());
            }));

        /////Dick state
            /////Transitions
            dick->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge();
            }),ascend_prime);

            dick->add_transition(std::function<bool()>([](){
                return dick_button->is_rising_edge();
            }),store);

            /////Entry and exit functions
            dick->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                std::cout << "Dick Entry" << std::endl;
                Arm::pid_controller->set_target(500);
                Elbow::pid_controller->set_target(2000);
            }));
            dick->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                std::cout << "Dick Exit" << std::endl;
            }));

        /////Ascend Prime State
            /////Transitions
            ascend_prime->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge() || Elbow::pid_controller->is_in_range(PID_TOLERANCE);
            }),ascend);

            /////Entry and exit functions
            ascend_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Ascend Prime Entry" << std::endl;
                Arm::pid_controller->set_target(500);
                Elbow::pid_controller->set_target(4000);
            }));
            ascend_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Ascend Prime Exit" << std::endl;
            }));

        /////Ascend State
            /////Transitions
            ascend->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge();
            }),zero_arm);

            /////Entry and exit functions
            ascend->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Ascend Entry" << std::endl;
                Arm::pid_controller->set_target(100);
                Elbow::pid_controller->set_target(4000);
                Wrist::intake_motor->set_operation(std::function<int16_t()>([](){
                    return -3.2*((BaseReadable::driver_controller->get_analog(DRIVETRAIN_THROTTLE) * 12000) / 127);
                }),cap_arm->get_name());
            }));
            ascend->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Ascend Exit" << std::endl;
                Wrist::intake_motor->set_operation(idle_intake_function,cap_arm->get_name());
            }));

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
            }),score_prime);
            store->add_transition(std::function<bool()>([](){
                return dick_button->is_rising_edge();
            }),dick);

            /////Entry and exit functions
            store->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                std::cout << "Store Entry" << std::endl;
                Arm::pid_controller->set_bounds(-8000,8000);
                Arm::left_motor->set_operation(std::function<int16_t()>([](){
                    return Arm::pid_controller->get_pid_value();
                }),cap_arm->get_name());
                Arm::right_motor->set_operation(std::function<int16_t()>([](){
                    return Arm::pid_controller->get_pid_value();
                }),cap_arm->get_name());
                Wrist::flipping_motor->set_operation(std::function<int16_t()>([](){
                    return Wrist::pid_controller->get_pid_value();
                }),cap_arm->get_name());
                Arm::pid_controller->set_target(-30);
                Elbow::pid_controller->set_target(ELBOW_STORE_POSITION);
            }));
            store->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Store Entry" << std::endl;
                Arm::pid_controller->set_bounds(-12000,12000);
            }));

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
                return dick_button->is_rising_edge();
            }),dick);

            /////Entry/Exit Functions
            ground->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Ground Entry" << std::endl;
                if(prev_state == store){
                    Wrist::pid_controller->set_target(0);
                }
                Arm::pid_controller->set_target(ARM_GROUND_POSITION);
                Elbow::pid_controller->set_target(ELBOW_GROUND_POSITION);
            }));
            ground->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Ground Exit" << std::endl;
            }));

        /////Flip Low State
            /////Transitions
            flip_low->add_transition(std::function<bool()>([](){
                return Wrist::pid_controller->is_in_range(PID_TOLERANCE);
            }),ground);

            /////Entry/Exit Functions
            flip_low->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Flip Low Entry" << std::endl;
                Arm::pid_controller->set_target(ARM_FLIP_LOW_POSITION);
                Wrist::pid_controller->set_target(wrist_flip_target());
            }));
            flip_low->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Flip Low Exit" << std::endl;
            }));

        /////Flip High State
            /////Transitions
            flip_high->add_transition(std::function<bool()>([](){
                return Wrist::pid_controller->is_in_range(PID_TOLERANCE);
            }),store);

            /////Entry/Exit Functions
            flip_high->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Flip High Entry" << std::endl;
                Elbow::pid_controller->set_target(ELBOW_FLIP_HIGH_POSITION);
                Wrist::pid_controller->set_target(wrist_flip_target());
            }));
            flip_high->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Flip High Exit" << std::endl;
            }));

        /////Score Prime State
            /////Transitions
            score_prime->add_transition(std::function<bool()>([](){
                return down_button->is_rising_edge();
            }),store);
            score_prime->add_transition(std::function<bool()>([](){
                return !cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && !BaseReadable::driver_controller->is_digital_pressed(ELEVATE_BUTTON);
            }),score);
            score_prime->add_transition(std::function<bool()>([](){
                return cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE);
            }),score_flip);
            score_prime->add_transition(std::function<bool()>([](){
                if(descore_button->is_rising_edge()){
                    cap_arm->metadata().is_stealing = true;
                    return true;
                }
                return false;
            }),descore_prime);

            /////Entry/Exit Functions
            score_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Score Prime Entry" << std::endl;
                Arm::pid_controller->set_target(ARM_SCORE_PRIME_POSITION);
                Elbow::pid_controller->set_target(ELBOW_SCORE_PRIME_POSITION);
            }));
            score_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Score Prime Exit" << std::endl;
                if(next_state == store || next_state == zero_arm){
                    Wrist::intake_motor->set_operation(idle_intake_function, cap_arm->get_name());
                }
            }));

        /////Score Flip State
            /////Transitions
            score_flip->add_transition(std::function<bool()>([](){
                return Wrist::pid_controller->is_in_range(PID_TOLERANCE);
            }),score);

            /////Entry/Exit Functions
            score_flip->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Score Flip Entry" << std::endl;
                cap_arm->metadata().is_stealing = false;
                Wrist::pid_controller->set_target(wrist_flip_target());
            }));
            score_flip->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Score Flip Entry" << std::endl;
            }));

        ////Score State
            /////Transitions
            score->add_transition(std::function<bool()>([](){
                return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && cap_arm->metadata().is_stealing;
            }),score_prime);
            score->add_transition(std::function<bool()>([](){
                return Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && !cap_arm->metadata().is_stealing;
            }),descore_prime);

            /////Entry/Exit Function
            score->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Score Entry" << std::endl;
                Arm::pid_controller->set_target(ARM_SCORE_POSITION);
                Elbow::pid_controller->set_target(ELBOW_SCORE_POSITION);
                if(prev_state == descore_prime){
                    Wrist::intake_motor->set_value(INTAKE_VOLTAGE,cap_arm->get_name());
                }
            }));
            score->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Score Exit" << std::endl;
                if(next_state == score_prime){
                    Wrist::intake_motor->set_value(IDLE_VOLTAGE,cap_arm->get_name());
                }
            }));

        ////Descore Prime State
            /////Transitions
            descore_prime->add_transition(std::function<bool()>([](){
                return cap_arm->metadata().is_stealing && down_button->is_rising_edge();
            }),store);
            descore_prime->add_transition(std::function<bool()>([](){
                return !cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE);
            }),zero_arm);
            descore_prime->add_transition(std::function<bool()>([](){
                return cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) && Elbow::pid_controller->is_in_range(PID_TOLERANCE) && !BaseReadable::driver_controller->is_digital_pressed(DESCORE_BUTTON);
            }),score);
            descore_prime->add_transition(std::function<bool()>([](){
                if(elevate_button->is_rising_edge()){
                    cap_arm->metadata().is_stealing = false;
                    return true;
                }
                return false;
            }),score_prime);

            /////Entry/Exit Functions
            descore_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // std::cout << "Descore Prime Entry" << std::endl;
                Arm::pid_controller->set_target(ARM_DESCORE_PRIME_POSITION);
                Elbow::pid_controller->set_target(ELBOW_DESCORE_PRIME_POSITION);
                if(prev_state == score){
                    Wrist::intake_motor->set_value(-INTAKE_VOLTAGE,cap_arm->get_name());
                }
            }));
            descore_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                // std::cout << "Descore Prime Exit" << std::endl
                if(next_state == zero_arm) {
                    Wrist::intake_motor->set_operation(idle_intake_function,cap_arm->get_name());
                }
            }));

        ////Descore Prime States
            /////Transition

            /////Entry/Exit Function
            angled_pickup->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Arm::pid_controller->set_target(ARM_ANGLE_PICKUP);
                Elbow::pid_controller->set_target(ELBOW_ANGLE_PICKUP);
                Wrist::intake_motor->set_value(INTAKE_VOLTAGE, cap_arm->get_name());
            }));
            angled_pickup->set_on_state_exit(std::function<void(state*)>([](state* next_state){
                Wrist::intake_motor->set_value(IDLE_VOLTAGE, cap_arm->get_name());
            }));

            ball_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Arm::pid_controller->set_target(ARM_ANGLE_PICKUP - 300);
                Elbow::pid_controller->set_target(ELBOW_GROUND_POSITION - 800);
            }));
            ball_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){

            }));

            ball_sweep->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Arm::pid_controller->set_target(ARM_ANGLE_PICKUP - 300);
                Elbow::pid_controller->set_target(ELBOW_GROUND_POSITION);
            }));
            ball_sweep->set_on_state_exit(std::function<void(state*)>([](state* next_state){

            }));

        cap_arm->add_state(zero_arm);
        cap_arm->add_state(zero_elbow);
        cap_arm->add_state(store);
        cap_arm->add_state(ground);
        cap_arm->add_state(flip_low);
        cap_arm->add_state(flip_high);
        cap_arm->add_state(score_prime);
        cap_arm->add_state(score_flip);
        cap_arm->add_state(score);
        cap_arm->add_state(descore_prime);
        cap_arm->add_state(dick);
        cap_arm->add_state(ascend_prime);
        cap_arm->add_state(ascend);
        cap_arm->add_state(angled_pickup);
        cap_arm->add_state(ball_prime);
        cap_arm->add_state(ball_sweep);
        cap_arm->set_state(zero_arm);
    }
}
