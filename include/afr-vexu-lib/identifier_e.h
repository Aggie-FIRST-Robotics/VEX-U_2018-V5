#ifndef VEX_U_2018_V5_IDENTIFIER_E_H
#define VEX_U_2018_V5_IDENTIFIER_E_H

#include <string>

namespace AFR::VexU{
    class identifer_e{
        std::string identifer_;

    public:
        explicit identifer_e(const std::string& identifier);

        std::string get_identifer() const;
    };
}

#endif //VEX_U_2018_V5_IDENTIFIER_E_H
