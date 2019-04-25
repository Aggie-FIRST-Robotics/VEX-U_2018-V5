#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"
#include "rev/cap/cap.h"

namespace AFR::VexU::Rev::Cap{

    /////State Controlle
    state_controller<cap_arm_meta>* cap_arm = nullptr;

    /////States
//    state* zero_arm = nullptr;
    state* ground = nullptr;
    state* flip = nullptr;
    state* score_prime = nullptr;
    state* score_flip = nullptr;
    state* score = nullptr;
    state* descore_prime = nullptr;
    state* analog_arm = nullptr;

    /////Edge detection for button lambda
    BaseReadable::digital_edge_detector* elevate_button = nullptr;
    BaseReadable::digital_edge_detector* down_button = nullptr;
    BaseReadable::digital_edge_detector* descore_button = nullptr;
    BaseReadable::digital_edge_detector* flip_button = nullptr;
    BaseReadable::digital_edge_detector* reset_button = nullptr;

    std::function<int16_t()> idle_intake_function{};

    std::function<int16_t()> zero_arm_action{};
    std::function<int16_t()> zero_wrist_action{};
    std::function<int16_t()> wrist_flip_target{};
    std::function<int16_t()> analog_arm_action{};

    bool arm_zeroed = false;
    bool wrist_zeroed = false;

    double analog_arm_val = 0.0;

    BaseReadable::adi_digital_readable* limit_switch{};

    void init(){
        cap_arm = new state_controller<cap_arm_meta>(UPDATE_PERIOD, cap_arm_meta{false}, "cap arm state controller");

        Arm::init();
        Wrist::init();

        limit_switch = Arm::limit_switch;

        // zero_arm = new state("zero_shoulder");
        ground = new state("ground");
        flip = new state("flip");
        score_prime = new state("score prime");
        score_flip = new state("score flip");
        score = new state("score");
        descore_prime = new state("descore prime");
        analog_arm = new state("analog arm");

        elevate_button = new BaseReadable::digital_edge_detector(CONTROLLER_PARTNER, ELEVATE_BUTTON, "elevate button edge");
        down_button = new BaseReadable::digital_edge_detector(CONTROLLER_PARTNER, DOWN_BUTTON, "ground button edge");
        descore_button = new BaseReadable::digital_edge_detector(CONTROLLER_PARTNER, DESCORE_BUTTON,
                                                                 "steal button edge");
        flip_button = new BaseReadable::digital_edge_detector(CONTROLLER_PARTNER, FLIP_BUTTON, "flip button edge");
        reset_button = new BaseReadable::digital_edge_detector(CONTROLLER_PARTNER, RESET_BUTTON, "zero button edge");

        std::cout << "Setting controller operations" << std::endl;

        idle_intake_function = []() -> int16_t{
            if(BaseReadable::operator_controller->is_digital_pressed(INTAKE_BUTTON)){
                return INTAKE_VOLTAGE;
            }
            else if(BaseReadable::operator_controller->is_digital_pressed(OUTTAKE_BUTTON)){
                return -INTAKE_VOLTAGE;
            }
            else{
                return IDLE_VOLTAGE;
            }
        };

        zero_arm_action = []() -> int16_t{
            if(arm_zeroed){
                return Arm::pid_controller->get_pid_value();
            }
            if(Arm::limit_switch->is_pressed()){
                Arm::encoder->tare_position();
                arm_zeroed = true;
                return Arm::pid_controller->get_pid_value();
            }
            else{
                return -12000;
            }
        };

        zero_wrist_action = []() -> int16_t{
            if(wrist_zeroed){
                return Wrist::pid_controller->get_pid_value();
            }
            if(Wrist::limit_switch->is_pressed()){
                Wrist::encoder->tare_position();
                wrist_zeroed = true;
                return Wrist::pid_controller->get_pid_value();
            }
            else{
                return -12000;
            }
        };

        wrist_flip_target = []() -> int16_t{
            if(flip_button->is_rising_edge()){
                if(Wrist::pid_controller->get_last_target() == 0){
                    Wrist::pid_controller->set_target(WRIST_FLIP_POSITION);
                    wrist_zeroed = true;
                }
                else {
                    Wrist::pid_controller->set_target(0);
                    wrist_zeroed = false;
                }
            }
            if(wrist_zeroed){
                return Wrist::pid_controller->get_pid_value();
            }
            return zero_wrist_action();
        };

        analog_arm_action = []() -> int16_t{
            analog_arm_val += BaseReadable::operator_controller->get_analog(ARM_STICK) / 127.0 * 3.0;
            Arm::pid_controller->set_target(analog_arm_val);
            return Arm::pid_controller->get_pid_value();
        };

        Arm::pid_controller->set_operation(std::function<double()>([](){
            return Arm::encoder->get_scaled_position();
        }), cap_arm->get_name());
        Arm::left_motor->set_operation(std::function<int16_t()>([](){
            return Arm::pid_controller->get_pid_value();
        }), cap_arm->get_name());
        Arm::right_motor->set_operation(std::function<int16_t()>([](){
            return Arm::pid_controller->get_pid_value();
        }), cap_arm->get_name());

        Wrist::pid_controller->set_operation(std::function<double()>([](){
            return Wrist::encoder->get_scaled_position();
        }), cap_arm->get_name());
        Wrist::pid_controller->set_target(0);
        Wrist::flipping_motor->set_operation(wrist_flip_target, cap_arm->get_name());

        Wrist::intake_motor->set_operation(idle_intake_function, cap_arm->get_name());

        // /////Zero Shoulder
        // zero_arm->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
        //     Arm::left_motor->set_operation(zero_arm_action,cap_arm->get_name());
        //     Arm::right_motor->set_operation(zero_arm_action,cap_arm->get_name());
        //     Wrist::intake_motor->set_operation(zero_wrist_action,cap_arm->get_name());
        // }));
        // zero_arm->set_on_state_exit(std::function<void(state*)>([](state* next_state){
        //     Arm::pid_controller->set_target(-30);
        //     Wrist::pid_controller->set_target(0);
        //     Arm::left_motor->set_operation(std::function<int16_t()>([](){
        //         return Arm::pid_controller->get_pid_value();
        //     }),cap_arm->get_name());
        //     Arm::right_motor->set_operation(std::function<int16_t()>([](){
        //         return Arm::pid_controller->get_pid_value();
        //     }),cap_arm->get_name());
        //     Wrist::flipping_motor->set_operation(std::function<int16_t()>([](){
        //         return Wrist::pid_controller->get_pid_value();
        //     }),cap_arm->get_name());
        // }));

        // zero_arm->add_transition(std::function<bool()>([](){
        //     if(Arm::debounce->is_triggered()){
        //         Arm::encoder->tare_position();
        //         return true;
        //     }
        //     return false;
        // }),ground);

        /////Store stat
        ground->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Ground entry" << std::endl;
            cap_arm->metadata().is_stealing = false;

            Arm::pid_controller->set_target(0);
            // Arm::left_motor->set_operation(zero_arm_action, cap_arm->get_name());
            // Arm::right_motor->set_operation(zero_arm_action, cap_arm->get_name());

            Wrist::intake_motor->set_operation(idle_intake_function, cap_arm->get_name());

            arm_zeroed = false;
//            wrist_zeroed = false;
        }));
        ground->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            Arm::left_motor->set_operation(std::function<int16_t()>{[]() -> int16_t{
                return Arm::pid_controller->get_pid_value();
            }}, cap_arm->get_name());
            Arm::right_motor->set_operation(std::function<int16_t()>{[]() -> int16_t{
                return Arm::pid_controller->get_pid_value();
            }}, cap_arm->get_name());
            // Wrist::flipping_motor->set_operation(wrist_flip_target, cap_arm->get_name());
            Wrist::intake_motor->set_value(IDLE_VOLTAGE, cap_arm->get_name());
            std::cout << "Ground exit" << std::endl;
        }));

        // ground->add_transition(std::function<bool()>([](){
        //     return reset_button->is_rising_edge();
        // }),zero_arm);
        ground->add_transition(std::function<bool()>([](){
            return BaseReadable::operator_controller->is_digital_pressed(FLIP_BUTTON);
        }), flip);
        ground->add_transition(std::function<bool()>([](){
            return descore_button->is_rising_edge();
        }), descore_prime);
        ground->add_transition(std::function<bool()>([](){
            return elevate_button->is_rising_edge();
        }), score_prime);
        ground->add_transition(std::function<bool()>([](){
            return BaseReadable::operator_controller->is_digital_pressed(ANALOG_ARM_BUTTON);
        }), analog_arm);

        /////Flip Low State
        flip->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Flip entry" << std::endl;
            Arm::pid_controller->set_target(ARM_FLIP_LOW_POSITION);
        }));
        flip->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Flip exit" << std::endl;
        }));

        flip->add_transition(std::function<bool()>([](){
            return Wrist::pid_controller->is_in_range(PID_TOLERANCE);
        }), ground);

        /////Score Prime State
        score_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Score prime entry" << std::endl;
            Arm::pid_controller->set_target(ARM_SCORE_PRIME_POSITION);
        }));
        score_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Score prime exit" << std::endl;
        }));

        score_prime->add_transition(std::function<bool()>([](){
            return down_button->is_rising_edge();
        }), ground);
        score_prime->add_transition(std::function<bool()>([](){
            return descore_button->is_rising_edge();
        }), descore_prime);
        score_prime->add_transition(std::function<bool()>([](){
            return !cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) &&
                   !BaseReadable::operator_controller->is_digital_pressed(ELEVATE_BUTTON);
        }), score);
        score_prime->add_transition(std::function<bool()>([](){
            return cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE);
        }), score_flip);



        /////Score Flip State
        score_flip->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Score flip entry" << std::endl;
            cap_arm->metadata().is_stealing = false;
            if(Wrist::pid_controller->get_last_target() == 0){
                Wrist::pid_controller->set_target(WRIST_FLIP_POSITION);
                wrist_zeroed = true;
            }
            else {
                Wrist::pid_controller->set_target(0);
                wrist_zeroed = false;
            }
        }));
        score_flip->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Score flip exit" << std::endl;

        }));
        score_flip->add_transition(std::function<bool()>([](){
            return Wrist::pid_controller->is_in_range(PID_TOLERANCE);
        }), score);

        ////Score State
        score->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Score entry" << std::endl;
            Arm::pid_controller->set_target(ARM_DESCORE_PRIME_POSITION);
        }));
        score->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Score exit" << std::endl;
            if(next_state == score_prime){
                Wrist::intake_motor->set_value(IDLE_VOLTAGE, cap_arm->get_name());
            }
        }));

        score->add_transition(std::function<bool()>([](){
            return Arm::pid_controller->is_in_range(PID_TOLERANCE) && cap_arm->metadata().is_stealing;
        }), score_prime);
        score->add_transition(std::function<bool()>([](){
            return Arm::pid_controller->is_in_range(PID_TOLERANCE) && !cap_arm->metadata().is_stealing;
        }), descore_prime);

        ////Descore Prime State
        descore_prime->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
            std::cout << "Descore entry" << std::endl;
            Arm::pid_controller->set_target(ARM_DESCORE_PRIME_POSITION);
            if(prev_state == score){
                Wrist::intake_motor->set_value(-INTAKE_VOLTAGE, cap_arm->get_name());
            }
            else{
                cap_arm->metadata().is_stealing = true;
                Wrist::intake_motor->set_value(INTAKE_VOLTAGE, cap_arm->get_name());
            }
        }));
        descore_prime->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Descore exit" << std::endl;
            if(next_state == score){
                Wrist::intake_motor->set_value(INTAKE_VOLTAGE, cap_arm->get_name());
            }
        }));

        descore_prime->add_transition(std::function<bool()>([](){
            return down_button->is_rising_edge();
        }), ground);
        descore_prime->add_transition(std::function<bool()>([](){
            return cap_arm->metadata().is_stealing && Arm::pid_controller->is_in_range(PID_TOLERANCE) &&
                   !BaseReadable::operator_controller->is_digital_pressed(DESCORE_BUTTON);
        }), score);

        //Analog Arm
        analog_arm->set_on_state_entry(std::function<void(state*)>([](state* next_state){
            std::cout << "Analog Arm Entry" << std::endl;
            analog_arm_val = 0.0;
            Arm::left_motor->set_operation(analog_arm_action, cap_arm->get_name());
            Arm::right_motor->set_operation(analog_arm_action, cap_arm->get_name());
        }));
        analog_arm->set_on_state_exit(std::function<void(state*)>([](state* next_state){
            std::cout << "Analog Arm Exit" << std::endl;
            Arm::pid_controller->set_target(0);
        }));

        analog_arm->add_transition(std::function<bool()>([]() -> bool{
            return !BaseReadable::operator_controller->is_digital_pressed(ANALOG_ARM_BUTTON);
        }), ground);

        // cap_arm->add_state(zero_arm);
        cap_arm->add_state(ground);
        cap_arm->add_state(flip);
        cap_arm->add_state(score_prime);
        cap_arm->add_state(score_flip);
        cap_arm->add_state(score);
        cap_arm->add_state(descore_prime);
        cap_arm->add_state(analog_arm);
    }
}

#pragma clang diagnostic pop