#ifndef VEX_U_2018_V51_BATTERY_READABLE_H
#define VEX_U_2018_V51_BATTERY_READABLE_H

#include "main.h"

#include "afr-lib/nameable.h"

namespace AFR::VexU::BaseReadable {
    class battery_readable : public virtual nameable {

    public:
        battery_readable();
        double get_capacity();
        double get_current();
        double get_temperature();
        double get_voltage();
    };
}
#endif //VEX_U_2018_V51_BATTERY_READABLE_H
