#include "Module.h"

const std::string Module::to_string() const {
    std::ostringstream ret;

    for(auto i: _slices) {
        ret << i.to_string() << std::endl;
    }
    return ret.str() + get_net();
}

const std::string Module::get_net() const {
    std::stringstream ret;

    for(auto i: _net) {
        if(!i.second.empty()) {
            ret << "net \"";
            ret << i.first << "\" ," << std::endl << i.second.to_string() << ";" << std::endl;
        }
    }

    return ret.str();
}

Net* Module::add_interconnect(std::string name) {
    _net.insert(std::make_pair(name, Net()));
    return &(_net.at(name));
}

Net* Module::get_interconnect(std::string name) {
    return &(_net.at(name));
}
