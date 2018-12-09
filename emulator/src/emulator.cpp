#include <emulator/emulator.h>

namespace AFR::VexU::Emulator{
    emulator_error::emulator_error(const std::string& text) : runtime_error(text){}

    emulator::emulator() noexcept : port_map_(){}

    bool emulator::initialize(const std::vector<port_type>& ports){
        if(!is_initialized_){
            if(ports.size() != 21){
                throw emulator_error{"Invalid ports length: " + std::to_string(ports.size())};
            }
            for(unsigned int x = 0; x < ports.size(); x++){
                switch(ports[x]){
                    case MOTOR:{
                        port_map_.insert({x, new motor_data{}});
                        break;
                    }
                    default:{
                        throw emulator_error{"Unsupported thing: " + std::to_string(ports[x])};
                    }
                }
            }
            is_initialized_ = true;
            return true;
        }
        return false;
    }

    bool emulator::is_initialized() const{
        return false;
    }

//    port_data* emulator::add_port(const uint8_t& port, port_data* data){
//        if(port_map_.find(port) == port_map_.end()){
//            port_map_.insert({port, data});
//        }
//        else{
//            errno = EACCES;
//        }
//        return data;
//    }

    port_data* emulator::get_port(const uint8_t& port) const{
        return port_map_.at(port);
    }
}