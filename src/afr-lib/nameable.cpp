#include "afr-lib/nameable.h"

namespace AFR::VexU{
    std::unordered_map<std::string, nameable*> nameable::nameables_{};

    nameable::nameable(const std::string& name) : name_(name){
        if(!nameables_.emplace(name, this).second){
            throw std::runtime_error{"Cannot have multiple nameables named " + name};
        }
    }

    nameable::~nameable() {
        nameables_.erase(get_name());
    }

    void nameable::set_name(const std::string &name) {
        name_ = name;
    }

    nameable* nameable::find_nameable(const std::string& name){
        return nameables_.at(name);
    }
}
