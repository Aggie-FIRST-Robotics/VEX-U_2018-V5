#include "afr-vexu-lib/base-readable/competition_readable.h"

namespace AFR::VexU::BaseReadable {
    competition_readable* competition = nullptr;

    void competition_readable::update_private(const double& delta_seconds){}

    competition_readable::competition_readable() : readable(0, nullptr, "competition_readable"){}

    std::any competition_readable::get_value(){
        return pros::c::competition_get_status();
    }

    void init_competition(){
        competition = new competition_readable{};
    }

    void destroy_competition(){
        delete (competition);
    }
}
