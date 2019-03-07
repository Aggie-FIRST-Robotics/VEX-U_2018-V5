#ifndef VEX_U_2018_V5_AFR_VEXU_LIB_H
#define VEX_U_2018_V5_AFR_VEXU_LIB_H

#include "afr-vexu-lib/base-readable/battery_readable.h"
#include "afr-vexu-lib/base-readable/competition_readable.h"
#include "afr-vexu-lib/ports_list.h"

namespace AFR::VexU{
    void init_afr_vexu_lib(){
        BaseReadable::init_battery();
        BaseReadable::init_competition();
        init_ports_list();
    }
}

#endif //VEX_U_2018_V5_AFR_VEXU_LIB_H
