#ifndef VEX_U_2018_V5_EMULATOR_H
#define VEX_U_2018_V5_EMULATOR_H

#include <vector>
#include <unordered_map>

#include "data.h"

namespace AFR::VexU::Emulator{
    class emulator_error : public std::runtime_error{
    public:
        explicit emulator_error(const std::string& text);
    };

    class emulator{
        std::unordered_map<uint8_t, port_data*> port_map_;
        bool is_initialized_;

    public:
        emulator() noexcept;

        bool initialize(const std::vector<port_type>& ports);
        bool is_initialized() const;

//        port_data* add_port(const uint8_t& port, port_data* data);

        port_data* get_port(const uint8_t& port) const;
    };

    emulator main_emulator{};
}

#endif //VEX_U_2018_V5_EMULATOR_H
