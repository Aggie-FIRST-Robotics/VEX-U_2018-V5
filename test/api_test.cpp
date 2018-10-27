#include <main.h>
#include <any>

#include "afr-vexu-lib/commandable.h"
#include "afr-vexu-lib/identifier_e.h"
#include "afr-vexu-lib/ordered_readable.h"
#include "afr-vexu-lib/state.h"
#include "afr-vexu-lib/state_controller.h"
#include "afr-vexu-lib/subsystem_controller.h"
#include "afr-vexu-lib/transition.h"

int main(){
    std::vector<int> int_vector{};
    std::vector<double> double_vector{};
    int_vector.push_back(1);
    double_vector.push_back(2.9);

    std::any x = int_vector;

    std::vector<std::any> any_vector{};
    any_vector.emplace_back(int_vector);
    any_vector.emplace_back(double_vector);

    std::cout << std::any_cast<std::vector<int>>(any_vector.at(0)).at(0) << std::endl;
    std::cout << std::any_cast<std::vector<double>>(any_vector.at(1)).at(0) << std::endl;
}