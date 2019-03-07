#include "afr-lib/ports_list.h"

namespace AFR::VexU{
    std::vector<std::string>* ports_list = nullptr;

    void init_ports_list(){
        ports_list = new std::vector<std::string>{21 + 8};
        for(size_t x = 0; x < 21 + 8; x++){
            ports_list->emplace_back("");
        }
    }

    std::string get_smart_claim(port_t port){
        if(port < 1 || port > 21){
            throw std::runtime_error{"Bad port " + std::to_string(port) + " for smart search"};
        }
        return ports_list->at(static_cast<size_t>(port - 1));
    }

    void claim_smart(port_t port, const std::string& name){
        if(name.empty()){
            throw std::runtime_error{"Bad name for claiming smart port " + std::to_string(port)};
        }
        if(port < 1 || port > 21){
            throw std::runtime_error{"Bad port " + std::to_string(port) + " for smart claim for " + name};
        }
        auto port_index = static_cast<size_t>(port - 1);
        if(!ports_list->at(port_index).empty()){
            throw std::runtime_error{"Smart port " + std::to_string(port) + " already taken by " + get_smart_claim(port)
                                     + " trying to be claimed by " + name};
        }
        ports_list->at(port_index) = name;
    }

    std::string get_adi_claim(port_t port){
        if(port < 1 || port > 8){
            throw std::runtime_error{"Bad port " + std::to_string(port) + " for adi search"};
        }
        return ports_list->at(static_cast<size_t>(port + 20));
    }

    void claim_adi(port_t port, const std::string& name){
        if(name.empty()){
            throw std::runtime_error{"Bad name for claiming adi port " + std::to_string(port)};
        }
        if(port < 1 || port > 8){
            throw std::runtime_error{"Bad port " + std::to_string(port) + " for adi claim for " + name};
        }
        auto port_index = static_cast<size_t>(port + 20);
        if(!ports_list->at(port_index).empty()){
            throw std::runtime_error{"Adi port " + std::to_string(port) + " already taken by " + get_adi_claim(port)
                                     + " trying to be claimed by " + name};
        }
        ports_list->at(port_index) = name;
    }
}
