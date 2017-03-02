#include "Slicel.h"

int Slicel::slicel_count = 0;

Slicel::Slicel(const std::string &_name): _name(_name), _a("A"), _b("B"), _c("C"), _d("D"){

    //_PRECYINIT = "#OFF";
    //_SRUSEDMUX = "#OFF";
    //_SYNC_ATTR = "#OFF";
    _attributes.insert(std::make_pair("PRECYINIT", "#OFF"));
    _attributes.insert(std::make_pair("SRUSEDMUX", "#OFF"));
    _attributes.insert(std::make_pair("SYNC_ATTR", "#OFF"));
}

const std::string Slicel::to_string() const {
    return "inst \"" + _name + "\" \"SLICEL\", unplaced,\n" +
           "  cfg \" " +
           _a.to_string() + "       " +
           _b.to_string() + "       " +
           _c.to_string() + "       " +
           _d.to_string() + "       " +
           "PRECYINIT::" + _attributes.at("PRECYINIT") + " " +
           "SRUSEDMUX::" + _attributes.at("SRUSEDMUX") + " " +
           "SYNC_ATTR::" + _attributes.at("SYNC_ATTR") + " \";";
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

const std::string &Slicel::get_name() const {
    return _name;
}



