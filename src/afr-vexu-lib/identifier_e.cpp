#include <afr-vexu-lib/identifier_e.h>

AFR::VexU::identifier_e::identifier_e(const std::string& identifier) : identifier_(identifier){}

std::string AFR::VexU::identifier_e::get_identifier() const{
    return identifier_;
}
