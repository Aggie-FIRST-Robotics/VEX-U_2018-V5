#include <robot/catapult/catapult.h>
#include <robot/robot.h>

namespace AFR::VexU::Robot::Catapult{
    void init(){
            using namespace BaseCommandable;
            using namespace BaseReadable;
            using namespace BaseAction;

            nautilus_motor = new motor_commandable{
                    CATAPULT_MOTOR_PORT,
                    pros::E_MOTOR_GEARSET_INVALID,
                    false,
                    pros::E_MOTOR_BRAKE_INVALID
            };

            nautilus_limit_switch = new adi_digital_readable{LIMIT_SWITCH_UPDATE_PERIOD, NAUTALUS_LIMIT_SWITCH_PORT};
            nautalus_encoder = new motor_encoder_readable{
                    CATAPULT_MOTOR_PORT,
                    pros::E_MOTOR_GEARSET_INVALID,
                    false,
                    1.0,
                    ENCODER_UPDATE_PERIOD
            };

            hold_nautalus_action = new set_value_action<int16_t>{100, *nautilus_motor, -10};
            cock_nautalus_action = new set_value_action<int16_t>{100, *nautilus_motor, 50};
            stop_nautalus_action = new set_value_action<int16_t>{100, *nautilus_motor, 0};
            fire_nautalus_action = new set_value_action<int16_t>{100, *nautilus_motor, 100};

            hold_action_map.emplace("hold_action_nautilus", *hold_nautalus_action);
            cock_action_map.emplace("cock_action_nautilus", *cock_nautalus_action);
            stop_action_map.emplace("stop_action_nautilus", *stop_nautalus_action);
            fire_action_map.emplace("fire_action_nautilus", *fire_nautalus_action);

            cock_to_hold = [](bool& result) -> error_t{
                std::any out{};
                AFR_VEXU_INTERNAL_CALL(nautilus_limit_switch->get_value(out));
                result = std::any_cast<bool>(out);
                return error_t::SUCCESS;
            };
            hold_to_fire = [](bool& result) -> error_t{
                throw std::runtime_error{"Implement me!"};
            };
            fire_to_stop = [](bool& result) -> error_t{

            };
    }
}
