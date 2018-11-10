#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "modernize-pass-by-value"

#include <iostream>
#include <functional>
#include <thread>

#include "afr-vexu-lib/action.h"
#include "afr-vexu-lib/defines.h"
#include "afr-vexu-lib/ordered_input.h"
#include "afr-vexu-lib/state.h"
#include "afr-vexu-lib/state_controller.h"
#include "afr-vexu-lib/subsystem_controller.h"

//actions
#include "afr-vexu-lib/base_action/equivalent_value_action.h"
#include "afr-vexu-lib/base_action/set_value_action.h"

template<typename T>
class test_motor : public AFR::VexU::commandable{
    std::string name_;

    AFR::VexU::error_t set_value_private(const std::any& value) override;
    AFR::VexU::error_t check_value_private(const std::any& value, bool& result) override;

public:
    test_motor(const T& initial_value, const std::string& name);
};

template<typename T>
class test_sensor : public AFR::VexU::readable{
    std::string name_;

    AFR::VexU::error_t update_private(const double& delta_seconds) override;

public:
    test_sensor(const AFR::VexU::scheduled_update_t& update_period, const T& initial_value, const std::string& name);

    T value;
};

int main(){
    test_motor<int8_t> byte_motor{0, "byte_motor"};
    test_motor<int> int_motor{0, "int_motor"};
    test_sensor<bool> button1{1000, false, "button1"};
    test_sensor<bool> button2{500, false, "button2"};

    AFR::VexU::BaseAction::set_value_action<int8_t> stop_action_byte{400, byte_motor, 0};
    AFR::VexU::BaseAction::set_value_action<int> stop_action_int{800, int_motor, 0};
    AFR::VexU::BaseAction::set_value_action<int8_t> forward_action_byte{300, byte_motor, 127};
    AFR::VexU::BaseAction::set_value_action<int> forward_action_int{1200, int_motor, 1000};
    AFR::VexU::BaseAction::set_value_action<int8_t> backward_action_byte{100, byte_motor, -127};
    AFR::VexU::BaseAction::set_value_action<int> backward_action_int{2000, int_motor, -1000};

    std::unordered_map<std::string, AFR::VexU::action&> stop_action_map = {
            {"stop_action_byte", stop_action_byte},
            {"stop_action_int",  stop_action_int}
    };
    std::unordered_map<std::string, AFR::VexU::action&> forward_action_map = {
            {"forward_action_byte", forward_action_byte},
            {"forward_action_int",  forward_action_int}
    };
    std::unordered_map<std::string, AFR::VexU::action&> backward_action_map = {
            {"backward_action_byte", backward_action_byte},
            {"backward_action_int",  backward_action_int}
    };

    std::function<AFR::VexU::error_t(bool&)> to_forward{[button1](bool& result) -> AFR::VexU::error_t{
        std::any value;
        button1.get_value(value);
        result = std::any_cast<bool>(value);
        return AFR::VexU::SUCCESS;
    }};
    std::function<AFR::VexU::error_t(bool&)> stop_to_backward{[button2](bool& result) -> AFR::VexU::error_t{
        std::any value;
        button2.get_value(value);
        result = std::any_cast<bool>(value);
        return AFR::VexU::SUCCESS;
    }};
    std::function<AFR::VexU::error_t(bool&)> backward_to_stop{[button2](bool& result) -> AFR::VexU::error_t{
        std::any value;
        button2.get_value(value);
        result = !std::any_cast<bool>(value);
        return AFR::VexU::SUCCESS;
    }};
    std::function<AFR::VexU::error_t(bool&)> forward_to_stop{[button1](bool& result) -> AFR::VexU::error_t{
        std::any value;
        button1.get_value(value);
        result = !std::any_cast<bool>(value);
        return AFR::VexU::SUCCESS;
    }};

    const std::vector<AFR::VexU::transition> stop_transitions = {
            AFR::VexU::transition{to_forward, "forward"},
            AFR::VexU::transition{stop_to_backward, "backward"}
    };
    const std::vector<AFR::VexU::transition> forward_transitions = {
            AFR::VexU::transition{forward_to_stop, "stop"}
    };
    const std::vector<AFR::VexU::transition> backward_transitions = {
            AFR::VexU::transition{to_forward, "forward"},
            AFR::VexU::transition{backward_to_stop, "backward"}
    };

    const std::function<AFR::VexU::error_t(const AFR::VexU::state&)> on_stop_entry = [](
            const AFR::VexU::state& previous) -> AFR::VexU::error_t{
        std::cout << "Stop entered." << std::endl;
        return AFR::VexU::SUCCESS;
    };
    const std::function<AFR::VexU::error_t(const AFR::VexU::state&)> on_forward_entry = [](
            const AFR::VexU::state& previous) -> AFR::VexU::error_t{
        std::cout << "Forward entered." << std::endl;
        return AFR::VexU::SUCCESS;
    };
    const std::function<AFR::VexU::error_t(const AFR::VexU::state&)> on_backward_entry = [](
            const AFR::VexU::state& previous) -> AFR::VexU::error_t{
        std::cout << "Backward entered." << std::endl;
        return AFR::VexU::SUCCESS;
    };

    AFR::VexU::state stop{stop_action_map, stop_transitions, on_stop_entry};
    AFR::VexU::state forward{forward_action_map, forward_transitions, on_forward_entry};
    AFR::VexU::state backward{backward_action_map, backward_transitions, on_backward_entry};

    std::unordered_map<std::string, AFR::VexU::state&> states = {
            {"stop",     stop},
            {"forward",  forward},
            {"backward", backward}
    };
    std::unordered_map<std::string, AFR::VexU::commandable&> commandables{
            {"byte_motor", byte_motor},
            {"int_motor",  int_motor}
    };

    AFR::VexU::state_controller state_machine{350, states, commandables, "stop"};

    AFR::VexU::ordered_input button1_order{0, &button1};
    AFR::VexU::ordered_input button2_order{3, &button2};

    std::unordered_map<std::string, AFR::VexU::ordered_input&> inputs = {
            {"button1", button1_order},
            {"button2", button2_order}
    };

    std::unordered_map<std::string, AFR::VexU::state_controller&> state_machines = {
            {"main", state_machine}
    };

    AFR::VexU::subsystem_controller main_subsystem{inputs, state_machines};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true){
        main_subsystem.updateInputs();
        main_subsystem.updateStates();
        main_subsystem.updateActions();

        std::any value1;
        std::any value2;

        button1.get_value(value1);
        button2.get_value(value2);

        auto b1 = std::any_cast<bool>(value1);
        auto b2 = std::any_cast<bool>(value2);
        if(!b1){
            button1.value = true;
        }
        else{
            button1.value = false;
            button2.value = !b2;
        }
    }
#pragma clang diagnostic pop
}

template<typename T>
AFR::VexU::error_t test_motor<T>::set_value_private(const std::any& value){
    std::any value_result;
    commandable::get_current_value(value_result);

    if(std::any_cast<T>(value) != std::any_cast<T>(value_result)){
        std::cout << name_ << " set to " << std::any_cast<T>(value) << std::endl;
    }
    return AFR::VexU::SUCCESS;
}

template<typename T>
AFR::VexU::error_t test_motor<T>::check_value_private(const std::any& value, bool& result){
    result = value.type() == typeid(T);
    return AFR::VexU::SUCCESS;
}

template<typename T>
test_motor<T>::test_motor(const T& initial_value, const std::string& name) : commandable(initial_value), name_(name){}

template<typename T>
AFR::VexU::error_t test_sensor<T>::update_private(const double& delta_seconds){
    std::cout << name_ << " updated after " << delta_seconds << " seconds, set to " << value << std::endl;
    readable::value = value;
    return AFR::VexU::SUCCESS;
}

template<typename T>
test_sensor<T>::test_sensor(const AFR::VexU::scheduled_update_t& update_period, const T& initial_value,
                            const std::string& name) : readable(update_period, initial_value), name_(name),
                                                       value(initial_value){}

#pragma clang diagnostic pop