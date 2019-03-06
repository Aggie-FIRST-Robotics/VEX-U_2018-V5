#include "afr-vexu-lib/vaule.h"

namespace AFR::VexU{
    vaule::value(const std::any& initial_value, const std::string& name)
            :nameable(name), value(initial_value){}
}
