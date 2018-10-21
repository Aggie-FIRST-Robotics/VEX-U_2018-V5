#include <afr-vexu-lib/identifier_e.h>

AFR::VexU::identifer_e::identifer_e(const std::string& identifier) : identifer_(identifier){}

std::string AFR::VexU::identifer_e::get_identifer(){
    return identifer_;
}
