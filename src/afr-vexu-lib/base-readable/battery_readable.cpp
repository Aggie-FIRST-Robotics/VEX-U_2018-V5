#include "afr-vexu-lib/base-readable/battery_readable.h"

namespace AFR::VexU::BaseReadable {

    battery_readable::battery_readable()
            : nameable("battery"){}

    double battery_readable::get_capacity(){
        return pros::c::battery_get_capacity();
    }

    double battery_readable::get_current(){
        return pros::c::battery_get_current();
    }
    
    double battery_readable::get_temperature(){
        return pros::c::battery_get_temperature();
    }

    double battery_readable::get_voltage(){
        return pros::c::battery_get_voltage();
    }
}
