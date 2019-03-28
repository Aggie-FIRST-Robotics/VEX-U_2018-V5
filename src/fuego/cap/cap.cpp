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

    /////Transition Functions
    std::function<bool()> store_to_zero_shoulder{};
    std::function<bool()> store_to_ground{};
    std::function<bool()> store_to_flip{};
    std::function<bool()> store_to_steal{};
    std::function<bool()> store_to_score{};

    std::function<bool()> ground_to_store{};
    std::function<bool()> ground_to_flip{};
    std::function<bool()> ground_to_zero_shoulder{};
    std::function<bool()> ground_to_intake{};
    std::function<bool()> ground_to_spit{};

    std::function<bool()> flip_low_to_ground{};

    std::function<bool()> flip_high_to_store{};

    std::function<bool()> zero_arm_to_zero_elbow{};

    std::function<bool()> zero_elbow_to_store{};

    std::function<bool()> score_prime_to_score{};
    std::function<bool()> score_prime_to_store{};

    std::function<bool()> score_to_steal{};
    std::function<bool()> score_to_score_prime{};

    std::function<bool()> steal_to_score{};
    std::function<bool()> steal_to_store{};

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

        Arm::arm_pid_controller->set_operation(std::function<double()>([](){ return Arm::arm_encoder->get_scaled_position();}),cap_arm->get_name());
        Elbow::elbow_pid_controller->set_operation(std::function<double()>([](){return Elbow::elbow_encoder->get_scaled_position();}),cap_arm->get_name());
        Wrist::wrist_pid_controller->set_operation(std::function<double()>([](){return Wrist::wrist_encoder->get_scaled_position();}),cap_arm->get_name());

        /////Zero Shoulder
            //////Transitions
            zero_arm_to_zero_elbow = []() -> bool{ return Arm:};

        cap_arm->add_state(zero_arm);

        /////Zero Elbow
            /////Transitions
            //zero_elbow->add_transition(std::function<bool()>([](){ return Elbow::zero_action->is_zeroed();}),store);

            /////Entry/Exit Functions
                zero_elbow_entry = []() -> void{
                    /////Shoulder and arm go to zero
                };

                zero_elbow_exit = []() -> void{
                    /////stop zero actions
                };

            zero_elbow->set_on_state_entry(zero_elbow_entry);
            zero_elbow->set_on_state_exit(zero_elbow_exit);

        cap_arm->add_state(zero_elbow);

        /////Store state
                /////Transitions
                store_to_zero_shoulder = []() -> bool{
                    return reset_button->is_rising_edge();
                };

                store_to_ground = []() -> bool{
                    return down_button->is_rising_edge();
                };

                store_to_flip = []() -> bool{
                    return flip_button->is_rising_edge();
                };

                store_to_steal = []() -> bool{
                    cap_arm->metadata().is_stealing = descore_button->is_rising_edge();
                    return cap_arm->metadata().is_stealing;
                };

                store_to_score = []() -> bool{
                    return elevate_button->is_rising_edge();
                };

            store->add_transition(store_to_zero_shoulder, zero_arm);
            store->add_transition(store_to_ground, ground);
            store->add_transition(store_to_flip, flip_high);
            store->add_transition(store_to_steal, descore_prime);
            store->add_transition(store_to_score, score_prime);

                /////Entry and exit functions
                store_entry = []() -> void{
                    Arm::arm_pid_controller->set_target(0);
                    Elbow::elbow_pid_controller->set_target(ELBOW_STORE_POSITION);
                    Arm::left_arm_motor->set_operation(std::function<int16_t()>([](){return Arm::arm_pid_controller->get_pid_value();}), cap_arm->get_name());
                    Arm::right_arm_motor->set_operation(std::function<int16_t()>([](){return Arm::arm_pid_controller->get_pid_value();}), cap_arm->get_name());
                    Elbow::elbow_motor->set_operation(std::function<int16_t()>([](){return Elbow::elbow_pid_controller->get_pid_value();}), cap_arm->get_name());
                };

                store_exit = []() -> void {
                    Arm::left_arm_motor->set_value(0,cap_arm->get_name());
                    Arm::right_arm_motor->set_value(0,cap_arm->get_name());
                    Elbow::elbow_motor->set_value(0,cap_arm->get_name());
                };

            store->set_on_state_entry(store_entry);
            store->set_on_state_exit(store_exit);

        cap_arm->add_state(store);

        /////Ground state
                /////Transitions
                ground_to_store = []() -> bool{
                    return elevate_button->is_rising_edge();
                };

                ground_to_flip = []() -> bool{
                    return flip_button->is_rising_edge();
                };

                ground_to_zero_shoulder = []() -> bool{
                    return reset_button->is_rising_edge();
                };

                ground_to_intake = []() -> bool {
                    return GROUND_BUTTON();
                };

            ground->add_transition(ground_to_store,store);
            ground->add_transition(ground_to_flip,flip_low);
            ground->add_transition(ground_to_zero_shoulder,zero_arm);
            ground->add_transition(ground_to_intake,intake);





    }
}
