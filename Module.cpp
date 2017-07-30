#include "Module.h"

const std::string Module::to_string() const {
    std::ostringstream ret;

    ret << "module \"" << _name << "\" \"" << _inst_name << "\", cfg \"\";" << std::endl;

    for(auto i: _ports) {
        ret << i << std::endl;
    }

    ret << std::endl;

    for(auto i: _slices) {
        ret << i << std::endl;
    }

    ret << get_net();

    ret << "endmodule \"" << _name << "\";" << std::endl;

    return ret.str();
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

void Module::add_port(std::string portname, Slice& slice, std::string slice_port) {
    _ports.push_back(Port(portname, slice, slice_port));
}

std::deque<Slicel> &Module::get_slices() {
    return _slices;
}
