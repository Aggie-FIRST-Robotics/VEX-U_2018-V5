#include "rev/drive/drive.h"
namespace AFR::VexU::Rev::Drive{

    struct drive_meta {};

    /////State Controller
    state_controller<drive_meta>* drive_machine = nullptr;

    /////States
    state* low_gear = nullptr;
    state* high_gear = nullptr;

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
        low_gear = new state("low gear");
        high_gear = new state("high gear");

        gear_shift_button = new BaseReadable::digital_edge_detector(std::function<bool()>([](){
            return BaseReadable::driver_controller->is_digital_pressed(BALL_SWALLOW_BUTTON);
        }),"gear shift button");

        /////Initial Commandable Operations
        Base::right_motor_1->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Base::right_motor_2->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Base::right_motor_3->set_operation(std::function<int16_t()>([](){return THROTTLE() - TURN();}),drive_machine->get_name());
        Base::left_motor_1->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        Base::left_motor_2->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        Base::left_motor_3->set_operation(std::function<int16_t()>([](){return THROTTLE() + TURN();}),drive_machine->get_name());
        // Shifter::motor->set_operation(std::function<int16_t()>([](){
        //     return Shifter::dead_band->get_deadband_value();
        // }),drive_machine->get_name());

        /////Action operations
        Shifter::dead_band->set_operation(std::function<double()>([](){
            return Shifter::encoder->get_scaled_position();
        }),drive_machine->get_name());

        /////Manual Low Gear
            /////Entry/Exit Functions
            low_gear->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // Shifter::motor->set_value(-SHIFTER_VOLTAGE, drive_machine->get_name());
                Shifter::dead_band->set_target(SHIFTER_LOW_GEAR_TARGET);
            }));
            low_gear->set_on_state_exit(std::function<void(state*)>([](state* prev_state){

            }));

            /////Transitions
            low_gear->add_transition(std::function<bool()>([](){
                return gear_shift_button->is_rising_edge();
            }), high_gear);

        /////Auto High Gear
            /////Entry/Exit Functions
           high_gear->set_on_state_entry(std::function<void(state*)>([](state* prev_state){
                // Shifter::motor->set_value(SHIFTER_VOLTAGE, drive_machine->get_name());
                Shifter::dead_band->set_target(SHIFTER_HIGH_GEAR_TARGET);
            }));
            high_gear->set_on_state_exit(std::function<void(state*)>([](state* prev_state){

            }));

            /////Transitions
            high_gear->add_transition(std::function<bool()>([](){
                return gear_shift_button->is_rising_edge();
            }), low_gear);



        drive_machine->add_state(low_gear);
        drive_machine->add_state(high_gear);

        drive_machine->set_state(high_gear);
    }

    void destroy(){
        Base::destroy();
        Shifter::destroy();
        delete low_gear;
        delete high_gear;
        delete drive_machine;
        delete gear_shift_button;
    }
};
