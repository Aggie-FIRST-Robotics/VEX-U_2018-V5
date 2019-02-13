#ifndef VEX_U_2018_V5_COMPETITION_READABLE_H
#define VEX_U_2018_V5_COMPETITION_READABLE_H

#include "main.h"

#include "afr-vexu-lib/readable.h"

namespace AFR::VexU::BaseReadable {
    class competition_readable : public readable {
        void update_private(const double& delta_seconds) override;

    public:
        competition_readable();

        std::any get_value() override;
    };

    extern competition_readable* competition;

    void init_competition();
    void destroy_competition();
}
#endif //VEX_U_2018_V5_COMPETITION_READABLE_H
