#include "afr-vexu-lib/base-readable/competition_readable.h"

namespace AFR::VexU::BaseReadable {
    
    competition_readable::competition_readable() : nameable("competition_readable"){}

    uint8_t competition_readable::get_value(){
        return pros::c::competition_get_status();
    }
}
