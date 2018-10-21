#ifndef VEX_U_2018_V5_IDENTIFIER_E_H
#define VEX_U_2018_V5_IDENTIFIER_E_H

#include <string>

namespace AFR::VexU{
    class identifier_e{
        std::string identifier_;

    public:
        explicit identifier_e(const std::string& identifier);

        std::string get_identifier() const;
    };
}

#endif //VEX_U_2018_V5_IDENTIFIER_E_H
