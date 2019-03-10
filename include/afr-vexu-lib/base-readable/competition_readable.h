#ifndef VEX_U_2018_V5_COMPETITION_READABLE_H
#define VEX_U_2018_V5_COMPETITION_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable {
    class competition_readable : public virtual nameable {

    public:
        competition_readable();

        uint8_t get_status();
    };
}
#endif //VEX_U_2018_V5_COMPETITION_READABLE_H
