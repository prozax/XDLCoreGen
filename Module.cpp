#include "Module.h"

std::ostream &operator<<(std::ostream &os, Module const &rhs) {
    os << "module \"" << rhs._name << "\" \"" << rhs._inst_name << "\", cfg \"\"" << std::endl << ";" << std::endl;

//    for(auto i: rhs._ports) {
//        os << i << std::endl;
//    }

    os << std::endl;

    for (auto p: rhs._pins) {
        os << p.second << std::endl;
    }

    os << std::endl;

    for (auto i: rhs._slices) {
        os << i << std::endl;
    }

    os << std::endl;

    for (auto i: rhs._net) {
        os << i.second << std::endl;
    }

    os << "endmodule \"" << rhs._name << "\";" << std::endl;

    return os;
}


Net* Module::add_interconnect(const std::string name) {
    if(_net.count(name) == 0) {
        _net.insert(std::make_pair(name, Net(name)));
    }

    return &(_net.at(name));
}

Net* Module::get_interconnect(std::string pin_name) {
    return &(_net.at(pin_name));
}

void Module::add_ground_connection(const std::string instance_name, const std::string pin_name) {
    if(_net.count("GLOBAL_LOGIC0_" + _name) == 0) {
        _net.insert(std::make_pair("GLOBAL_LOGIC0_" + _name, Net("GLOBAL_LOGIC0_" + _name, "gnd")));
    }

    _net.at("GLOBAL_LOGIC0_" + _name).add_inpin(instance_name, pin_name);
}

void Module::add_vcc_connection(const std::string instance_name, const std::string pin_name) {
    if(_net.count("GLOBAL_LOGIC1_" + _name) == 0) {
        _net.insert(std::make_pair("GLOBAL_LOGIC1_" + _name, Net("GLOBAL_LOGIC1_" + _name, "vcc")));
    }

    _net.at("GLOBAL_LOGIC1_" + _name).add_inpin(instance_name, pin_name);
}

void Module::add_port(std::string portname, Slice& slice, std::string slice_port) {
    _ports.push_back(Port(portname, slice, slice_port));
}

std::deque<Slicel> &Module::get_slices() {
    return _slices;
}
