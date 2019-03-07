#ifndef VEX_U_2018_V5_PORTS_LIST_H
#define VEX_U_2018_V5_PORTS_LIST_H

#include <vector>

#include "afr-lib/defines.h"

namespace AFR::VexU{
    void init_ports_list();
    void destroy_ports_list();

    std::string get_smart_claim(port_t port);
    void claim_smart(port_t port, const std::string& name);

    std::string get_adi_claim(port_t port);
    void claim_adi(port_t port, const std::string& name);
}

#endif //VEX_U_2018_V5_PORTS_LIST_H
