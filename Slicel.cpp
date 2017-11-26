#include "Slicel.h"

int Slicel::_slicel_count = 0;

Slicel::Slicel(const std::string &_name): Slice(_name), _a("A"), _b("B"), _c("C"), _d("D"){
    _attributes.insert(std::make_pair("PRECYINIT", "#OFF"));
    _attributes.insert(std::make_pair("SRUSEDMUX", "#OFF"));
    _attributes.insert(std::make_pair("SYNC_ATTR", "#OFF"));
    _attributes.insert(std::make_pair("COUTUSED", "#OFF"));
    _attributes.insert(std::make_pair("CLKINV", "#OFF"));

    _slicel_count++;
}

std::ostream &operator<<(std::ostream &os, Slicel const &rhs) {
    os << "inst \"" << rhs._name << R"(" "SLICEL", )";

    if(rhs.is_placed())
        os << "placed " << rhs._primitive_site->get_parent()->get_name() << " "
           << rhs._primitive_site->get_name() << "," << std::endl;
    else
        os << "unplaced ," << std::endl;

    os << "  cfg \" ";
    os << rhs._a;
    os << rhs._b;
    os << rhs._c;
    os << rhs._d;
    os << "PRECYINIT::" << rhs._attributes.at("PRECYINIT") << " ";
    os << "SRUSEDMUX::" << rhs._attributes.at("SRUSEDMUX") << " ";
    os << "COUTUSED::" << rhs._attributes.at("COUTUSED") << " ";
    os << "CLKINV::" << rhs._attributes.at("CLKINV") << " ";
    os << "SYNC_ATTR::" << rhs._attributes.at("SYNC_ATTR") << " \"" << std::endl << ";";

    return os;
}

void Slicel::set_attribute(std::string attr, std::string val) {
    if(_attributes.find(attr) != _attributes.end()) {
        _attributes[attr] = val;
    }
    else {
        switch (attr.at(0)) {
            case 'A':
                _a.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'B':
                _b.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'C':
                _c.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'D':
                _d.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            default:
                break;
        }
    }
}



