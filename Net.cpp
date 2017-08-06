
#include "Net.h"

Net::Net(const std::string &_name) : _name(_name), _type("") {}

Net::Net(const std::string &_name, const std::string &_type) : _name(_name), _type(_type) {}

Net* Net::set_outpin(std::string instance, std::string pin) {
    _outpin.clear();
    _outpin.insert(std::make_pair(instance, pin));
    return this;
}

Net* Net::add_inpin(std::string instance, std::string pin) {
    _inpins.insert(std::make_pair(instance, pin));
    return this;
}

const std::string Net::to_string() const {
    std::ostringstream ret;

    ret << "outpin \"";
    ret << _outpin.begin()->first << "\" \"" << _outpin.begin()->second << "\" ," << std::endl;

    for(auto const& i: _inpins) {
        ret << "inpin \"";
        ret << i.first << "\" \"" << i.second << "\" ," << std::endl;
    }

    return ret.str();
}

std::ostream &operator<<(std::ostream &os, Net const &rhs) {
     os << "net \"";
     os << rhs._name << "\" " << rhs._type << "," << std::endl;

    if(!rhs._outpin.empty()) {
        os << "outpin \"";
        os << rhs._outpin.begin()->first << "\" \"" << rhs._outpin.begin()->second << "\" ," << std::endl;
    }

    for(auto const& i: rhs._inpins) {
        os << "inpin \"";
        os << i.first << "\" \"" << i.second << "\" ," << std::endl;
    }

    os << ";" << std::endl;

    return os;
}

bool Net::empty() {
    return _outpin.empty() && _inpins.empty();
}
