#ifndef VEX_U_2018_V5_AFR_VEXU_LIB_H
#define VEX_U_2018_V5_AFR_VEXU_LIB_H

#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/base-readable/controller_readable.h"
#include "afr-vexu-lib/ports_list.h"
#include "afr-vexu-lib/comms/serial_manager.h"

namespace AFR::VexU {
    void init_afr_vexu_lib();
    void destroy_afr_vexu_lib();
}

#endif //VEX_U_2018_V5_AFR_VEXU_LIB_H
