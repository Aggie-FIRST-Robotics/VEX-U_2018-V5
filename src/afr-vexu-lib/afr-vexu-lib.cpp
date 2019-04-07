#include "afr-vexu-lib/afr-vexu-lib.h"
namespace AFR::VexU {
    void init_afr_vexu_lib(){
        init_serial_manager(5);
        BaseReadable::init_controllers();
        BaseReadable::init_battery();
        BaseReadable::init_competition();
        init_ports_list();
    }

    void destroy_afr_vexu_lib(){
        destroy_serial_manager();
        BaseReadable::destroy_controllers();
        BaseReadable::destroy_battery();
        BaseReadable::destroy_competition();
        destroy_ports_list();
    }
}