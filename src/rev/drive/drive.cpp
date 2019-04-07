#include "rev/drive/drive.h"
namespace AFR::VexU::Rev::Drive{

    struct drive_meta {};

    /////State Controller
    state_controller<drive_meta>* drive_machine = nullptr;

    /////States
    state* manual_low_gear = nullptr;
    state* auto_low_gear = nullptr;
    state* auto_high_gear = nullptr;

    /////Joystick Lambda
    std::function<int16_t()> THROTTLE = []() -> int16_t{ return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_THROTTLE) * 12000) / 127; };
    std::function<int16_t()> TURN = []() -> int16_t{ return (BaseReadable::driver_controller->get_analog(DRIVETRAIN_TURN) * 12000) / 127; };

    BaseReadable::digital_edge_detector* gear_shift_button = nullptr;


    void init(){
        Base::init();
        Shifter::init();

        /////State Machine
        drive_machine = new state_controller<drive_meta>(UPDATE_PERIOD,{},"drive state controller");

        /////States
        manual_low_gear = new state("manual low gear");
        auto_low_gear = new state("auto low gear");
        auto_high_gear = new state("auto high gear");

        gear_shift_button = new BaseReadable::digital_edge_detector(std::function<bool()>([](){
            return BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
        }),"gear shift button");

        /////Initial Commandable Operations
        Base::right_motor_1->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        Base::right_motor_2->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        Base::right_motor_3->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        Base::left_motor_1->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Base::left_motor_2->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Base::left_motor_3->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Shifter::motor->set_operation(std::function<int16_t()>([](){return Shifter::dead_band->get_deadband_value();}),drive_machine->get_name());

        /////Action operations
        Shifter::dead_band->set_operation(std::function<double()>([](){
            return Shifter::encoder->get_scaled_position();
        }),drive_machine->get_name());

        /////Manual Low Gear
            /////Entry/Exit Functions
            manual_low_gear->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Shifter::dead_band->set_target(SHIFTER_LOW_GEAR_TARGET);
            }));
            manual_low_gear->set_on_state_exit(std::function<void(state*)>([](state* prev_state){

            }));

            /////Transitions
            manual_low_gear->add_transition(std::function<bool()>([](){
                return gear_shift_button->is_rising_edge();
            }), auto_high_gear);

        /////Auto Low Gear
            /////Entry/Exit Functions
            auto_low_gear->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Shifter::dead_band->set_target(SHIFTER_LOW_GEAR_TARGET);
            }));
            auto_low_gear->set_on_state_exit(std::function<void(state*)>([](state* prev_state){

            }));

            /////Transitions
            auto_low_gear->add_transition(std::function<bool()>([](){
                return Base::left_motor_1_encoder->get_scaled_velocity() > LOW_TO_HIGH_SPEED_THRESHOLD;
            }), auto_high_gear);
            auto_low_gear->add_transition(std::function<bool()>([](){
                return gear_shift_button->is_rising_edge();
            }), manual_low_gear);

        /////Auto High Gear
            /////Entry/Exit Functions
            auto_high_gear->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                Shifter::dead_band->set_target(SHIFTER_HIGH_GEAR_TARGET);
            }));
            auto_high_gear->set_on_state_exit(std::function<void(state*)>([](state* prev_state){

            }));

            /////Transitions
            auto_high_gear->add_transition(std::function<bool()>([](){
                return Base::left_motor_1_encoder->get_scaled_velocity() < HIGH_TO_LOW_SPEED_THRESHOLD;
            }), auto_low_gear);
            auto_high_gear->add_transition(std::function<bool()>([](){
                return gear_shift_button->is_rising_edge();
            }), manual_low_gear);



        drive_machine->add_state(manual_low_gear);
        drive_machine->add_state(auto_low_gear);
        drive_machine->add_state(auto_high_gear);

        drive_machine->set_state(manual_low_gear);
    }

    void destroy(){
        Base::destroy();
        Shifter::destroy();
        delete manual_low_gear;
        delete auto_low_gear;
        delete auto_high_gear;
        delete drive_machine;
    }
};
