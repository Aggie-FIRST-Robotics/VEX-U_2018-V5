#include "fuego/cap/cap.h"
#include "fuego/fuego.h"
namespace AFR::VexU::Fuego::Cap{

    struct Cap_Arm_Meta{
        bool is_stealing;
    };

    /////State Controller
    state_controller<Cap_Arm_Meta>* cap_arm = nullptr;

    /////States
    state* zero_shoulder = nullptr;
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

    /////Entry/Exit Functions
    std::function<void()> zero_shoulder_entry{};
    std::function<void()> zero_shoulder_exit{};
    std::function<void()> zero_elbow_entry{};
    std::function<void()> zero_elbow_exit{};
    std::function<void()> store_entry{};
    std::function<void()> store_exit{};
    std::function<void()> ground_entry{};
    std::function<void()> ground_exit{};
    std::function<void()> flip_low_entry{};
    std::function<void()> flip_low_exit{};
    std::function<void()> flip_high_entry{};
    std::function<void()> flip_high_exit{};
    std::function<void()> score_prime_entry{};
    std::function<void()> score_prime_exit{};
    std::function<void()> descore_prime_entry{};
    std::function<void()> descore_prime_exit{};
    std::function<void()> intake_entry{};
    std::function<void()> intake_exit{};
    std::function<void()> spit_entry{};
    std::function<void()> spit_exit{};

    /////Button Lambda
    std::function<bool()> ELEVATE_BUTTON = []() -> bool{ return BaseReadable::driver_controller->get_L1(); };
    std::function<bool()> GROUND_BUTTON = []() -> bool{ return BaseReadable::driver_controller->get_L2(); };
    std::function<bool()> STEAL_BUTTON = []() -> bool{ return BaseReadable::driver_controller->get_R1(); };
    std::function<bool()> FLIP_BUTTON = []() -> bool{ return BaseReadable::driver_controller->get_X(); };
    std::function<bool()> ZERO_BUTTON = []() -> bool{ return BaseReadable::driver_controller->get_Y(); };

    /////Edge detection for button lambdas
    BaseReadable::digital_edge_detector* elevate_button = nullptr;
    BaseReadable::digital_edge_detector* ground_button = nullptr;
    BaseReadable::digital_edge_detector* steal_button = nullptr;
    BaseReadable::digital_edge_detector* flip_button = nullptr;
    BaseReadable::digital_edge_detector* zero_button = nullptr;

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

    std::function<bool()> zero_shoulder_to_zero_elbow{};

    std::function<bool()> zero_elbow_to_store{};

    std::function<bool()> score_prime_to_score{};
    std::function<bool()> score_prime_to_store{};

    std::function<bool()> score_to_steal{};
    std::function<bool()> score_to_score_prime{};

    std::function<bool()> steal_to_score{};
    std::function<bool()> steal_to_store{};

    void init(){
        //Readables
        cap_arm = new state_controller<Cap_Arm_Meta>(UPDATE_PERIOD,{false},"cap arm state controller");

        zero_shoulder = new state("zero_shoulder");
        zero_elbow = new state("zero_elbow");
        store = new state("store");
        ground = new state("ground");
        flip_low = new state("flip low");
        flip_high = new state("flip high");
        score_prime = new state("score prime");
        score = new state("score");
        descore_prime = new state("descore prime");

        elevate_button = new BaseReadable::digital_edge_detector(ELEVATE_BUTTON, "elevate button edge");
        ground_button = new BaseReadable::digital_edge_detector(GROUND_BUTTON, "ground button edge");
        steal_button = new BaseReadable::digital_edge_detector(STEAL_BUTTON, "steal button edge");
        flip_button = new BaseReadable::digital_edge_detector(FLIP_BUTTON, "flip button edge");
        zero_button = new BaseReadable::digital_edge_detector(ZERO_BUTTON, "zero button edge");

        Shoulder::pid_controller->set_operation(std::function<double()>([](){ return Shoulder::encoder->get_scaled_position();}),cap_arm->get_name());
        Elbow::pid_controller->set_operation(std::function<double()>([](){return Elbow::encoder->get_scaled_position();}),cap_arm->get_name());
        Wrist::pid_controller->set_operation(std::function<double()>([](){return Wrist::encoder->get_scaled_position();}),cap_arm->get_name());

        /////Zero Shoulder
            //////Transitions
            zero_shoulder->add_transition(std::function<bool()>([](){ return Shoulder::zero_action->is_zeroed();}),zero_elbow);

            /////Entry?Exit Functions
                zero_shoulder_entry = []() -> void{
                    /////Shoulder and arm go to zero
                };

                zero_shoulder_exit = []() -> void{
                    /////stop zero actions
                };

            zero_shoulder->set_on_state_entry(zero_shoulder_entry);
            zero_shoulder->set_on_state_exit(zero_shoulder_exit);

        cap_arm->add_state(zero_shoulder);

        /////Zero Elbow
            /////Transitions
            zero_elbow->add_transition(std::function<bool()>([](){ return Elbow::zero_action->is_zeroed();}),store);

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
                    return zero_button->is_rising_edge();
                };

                store_to_ground = []() -> bool{
                    return ground_button->is_rising_edge();
                };

                store_to_flip = []() -> bool{
                    return flip_button->is_rising_edge();
                };

                store_to_steal = []() -> bool{
                    cap_arm->metadata().is_stealing = steal_button->is_rising_edge();
                    return cap_arm->metadata().is_stealing;
                };

                store_to_score = []() -> bool{
                    return elevate_button->is_rising_edge();
                };

            store->add_transition(store_to_zero_shoulder, zero_shoulder);
            store->add_transition(store_to_ground, ground);
            store->add_transition(store_to_flip, flip_high);
            store->add_transition(store_to_steal, descore_prime);
            store->add_transition(store_to_score, score_prime);

                /////Entry and exit functions
                store_entry = []() -> void{
                    Shoulder::pid_controller->set_target(0);
                    Elbow::pid_controller->set_target(ELBOW_STORE_POSITION);
                    Shoulder::left_motor->set_operation(std::function<int16_t()>([](){return Shoulder::pid_controller->get_pid_value();}), cap_arm->get_name());
                    Shoulder::right_motor->set_operation(std::function<int16_t()>([](){return Shoulder::pid_controller->get_pid_value();}), cap_arm->get_name());
                    Elbow::elbow_motor->set_operation(std::function<int16_t()>([](){return Elbow::pid_controller->get_pid_value();}), cap_arm->get_name());
                };

                store_exit = []() -> void {
                    Shoulder::left_motor->set_value(0,cap_arm->get_name());
                    Shoulder::right_motor->set_value(0,cap_arm->get_name());
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
                    return zero_button->is_rising_edge();
                };

                ground_to_intake = []() -> bool {
                    return GROUND_BUTTON();
                };

            ground->add_transition(ground_to_store,store);
            ground->add_transition(ground_to_flip,flip_low);
            ground->add_transition(ground_to_zero_shoulder,zero_shoulder);
            ground->add_transition(ground_to_intake,intake);





    }
}
