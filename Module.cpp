#include "Module.h"

std::ostream &operator<<(std::ostream &os, Module const &rhs) {
    os << "module \"" << rhs._name << "_HARD_MACRO" << "\" \"" << rhs._inst_name << "\", cfg \"_SYSTEM_MACRO::FALSE\"" << std::endl << ";" << std::endl;

    for(auto i: rhs._ports) {
        os << i << std::endl;
    }

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

    os << "endmodule \"" << rhs._name<< "_HARD_MACRO" << "\";" << std::endl;

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
    if(_net.count("PORT_LOGIC0_" + _name) == 0) {
        // creating port and net for gnd
        add_port("gnd", instance_name, pin_name);
        _net.insert(std::make_pair("PORT_LOGIC0_" + _name, Net("PORT_LOGIC0_" + _name, "gnd")));
    }

    _net.at("PORT_LOGIC0_" + _name).add_inpin(instance_name, pin_name);
}

void Module::add_vcc_connection(const std::string instance_name, const std::string pin_name) {
    if(_net.count("PORT_LOGIC1_" + _name) == 0) {
        // creating port and net for vcc
        add_port("vcc", instance_name, pin_name);
        _net.insert(std::make_pair("PORT_LOGIC1_" + _name, Net("PORT_LOGIC1_" + _name, "vcc")));
    }

    _net.at("PORT_LOGIC1_" + _name).add_inpin(instance_name, pin_name);
}

void Module::add_port(std::string portname, std::string slice, std::string slice_port) {
    _ports.push_back(Port(portname, slice, slice_port));
}

void Module::add_port(std::string portname, Slice & slice, std::string slice_port) {
    add_port(portname, slice.get_name(), slice_port);
}

std::deque<Slicel> &Module::get_slices() {
    return _slices;
}


