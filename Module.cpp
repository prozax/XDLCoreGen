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
        ret << i.second << std::endl;
    }

    return ret.str();
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
    if(_net.count(_name + "LOGIC0") == 0) {
        _net.insert(std::make_pair(_name + "LOGIC0", Net(_name + "LOGIC0", "gnd")));
    }

    _net.at(_name + "LOGIC0").add_inpin(instance_name, pin_name);
}

void Module::add_vcc_connection(const std::string instance_name, const std::string pin_name) {
    if(_net.count(_name + "LOGIC1") == 0) {
        _net.insert(std::make_pair(_name + "LOGIC1", Net(_name + "LOGIC1", "vcc")));
    }

    _net.at(_name + "LOGIC1").add_inpin(instance_name, pin_name);
}

void Module::add_port(std::string portname, Slice& slice, std::string slice_port) {
    _ports.push_back(Port(portname, slice, slice_port));
}

std::deque<Slicel> &Module::get_slices() {
    return _slices;
}
