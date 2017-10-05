
#include "Net.h"

Net::Net(const std::string &_name) : _name(_name), _type(""), _outpin(Pin("", "")) {}

Net::Net(const std::string &_name, const std::string &_type) : _name(_name), _type(_type), _outpin(Pin("", "")) {}

Net* Net::set_outpin(std::string instance, std::string pin) {
    _outpin = Pin(instance, pin);
    return this;
}

Net* Net::add_inpin(std::string instance, std::string pin) {
    _inpins.emplace_back(instance, pin);
    return this;
}

std::ostream &operator<<(std::ostream &os, Net const &rhs) {
     os << "net \"";
//     os << rhs._name << "\" " << rhs._type << "," << std::endl;
    os << rhs._name << "\" " << "," << std::endl;

    if(!rhs._outpin.empty()) {
        os << "    " << "outpin \"";
        os << rhs._outpin.get_instance() << "\" " << rhs._outpin.get_pin() << " ," << std::endl;
    }

    for(const Pin& i: rhs._inpins) {
        os << "    " << "inpin \"";
        os << i.get_instance() << "\" " << i.get_pin() << " ," << std::endl;
    }

    os << ";" << std::endl;

    return os;
}

bool Net::empty() {
    return _outpin.empty() && _inpins.empty();
}

const std::string &Net::get_name() const {
    return _name;
}

const std::string &Net::get_type() const {
    return _type;
}

const std::vector<Pin> &Net::get_inpins() const {
    return _inpins;
}

Pin &Net::get_outpin() {
    return _outpin;
}
