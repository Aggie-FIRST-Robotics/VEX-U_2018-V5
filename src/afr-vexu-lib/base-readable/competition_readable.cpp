#include "afr-vexu-lib/base-readable/competition_readable.h"

namespace AFR::VexU::BaseReadable {

    competition_readable* competition = nullptr;

    void init_competition() {
        competition = new competition_readable();
    }

    void destroy_competition() {
        delete competition;
    }
    
    competition_readable::competition_readable() : nameable("competition_readable"){}

    uint8_t competition_readable::get_status(){
        return pros::c::competition_get_status();
    }
}
