#include "QuarterSlicel.h"

std::ostream &operator<<(std::ostream &os, QuarterSlicel const &rhs) {
    os << rhs._name << "5FFINIT::" <<  rhs._attributes.at("5FFINIT") << " "
       << rhs._name << "5FFMUX::" << rhs._attributes.at("5FFMUX") << " "
       << rhs._name << "5FFSR::" << rhs._attributes.at("5FFSR") << std::endl << "       ";

    if(rhs._attributes.at("5LUT") == "#OFF") {
        os << rhs._name << "5LUT::#OFF" << std::endl << "       ";
    }
    else {
        os << rhs._name << "5LUT:" << rhs._attributes.at("5LUTNAME") << ":#LUT:O5=" << rhs._attributes.at("5LUT")
           << std::endl << "       ";
    }

    if(rhs._attributes.at("6LUT") == "#OFF") {
        os << rhs._name << "6LUT::#OFF" << std::endl << "       ";
    }
    else {
        os << rhs._name << "6LUT:" << rhs._attributes.at("6LUTNAME") << ":#LUT:O6=" << rhs._attributes.at("6LUT")
           << std::endl << "       ";
    }


    os << rhs._name << "CY0::" << rhs._attributes.at("CY0") << " "
       << rhs._name << "FF:" << rhs._attributes.at("FFNAME") << ":" << rhs._attributes.at("FF") << " "
       << rhs._name << "FFINIT::" << rhs._attributes.at("FFINIT") << " "
       << rhs._name << "FFMUX::" << rhs._attributes.at("FFMUX") << " "
       << rhs._name << "FFSR::" << rhs._attributes.at("FFSR") << " "
       << rhs._name << "OUTMUX::" << rhs._attributes.at("OUTMUX") << " "
       << rhs._name << "USED::" << rhs._attributes.at("USED") << std::endl << "       ";

    return os;
}

QuarterSlicel::QuarterSlicel(const std::string &_name): _name(_name) {
    _attributes.insert(std::make_pair("5FFINIT", "#OFF"));
    _attributes.insert(std::make_pair("5FFMUX", "#OFF"));
    _attributes.insert(std::make_pair("5FFSR", "#OFF"));
    _attributes.insert(std::make_pair("5LUT", "#OFF"));
    _attributes.insert(std::make_pair("5LUTNAME", ""));
    _attributes.insert(std::make_pair("6LUT", "#OFF"));
    _attributes.insert(std::make_pair("6LUTNAME", ""));
    _attributes.insert(std::make_pair("CY0", "#OFF"));
    _attributes.insert(std::make_pair("FF", "#OFF"));
    _attributes.insert(std::make_pair("FFNAME", ""));
    _attributes.insert(std::make_pair("FFINIT", "#OFF"));
    _attributes.insert(std::make_pair("FFMUX", "#OFF"));
    _attributes.insert(std::make_pair("FFSR", "#OFF"));
    _attributes.insert(std::make_pair("OUTMUX", "#OFF"));
    _attributes.insert(std::make_pair("USED", "#OFF"));
}

QuarterSlicel::QuarterSlicel(const std::string &_name, const std::string &_5FFINIT, const std::string &_5FFMUX,
                             const std::string &_5FFSR, const std::string &_5LUT, const std::string &_5LUTNAME,
                             const std::string &_6LUT, const std::string &_6LUTNAME, const std::string &_CY0,
                             const std::string &_FF, const std::string &_FFINIT, const std::string &_FFMUX,
                             const std::string &_FFSR, const std::string &_OUTMUX, const std::string &_USED)
        : _name(_name) {
    _attributes.insert(std::make_pair("5FFINIT", _5FFINIT));
    _attributes.insert(std::make_pair("5FFMUX", _5FFMUX));
    _attributes.insert(std::make_pair("5FFSR", _5FFSR));
    _attributes.insert(std::make_pair("5LUT", _5LUT));
    _attributes.insert(std::make_pair("5LUTNAME", _5LUTNAME));
    _attributes.insert(std::make_pair("6LUT", _6LUT));
    _attributes.insert(std::make_pair("6LUTNAME", _6LUTNAME));
    _attributes.insert(std::make_pair("CY0", _CY0));
    _attributes.insert(std::make_pair("FF", _FF));
    _attributes.insert(std::make_pair("FFINIT", _FFINIT));
    _attributes.insert(std::make_pair("FFMUX", _FFMUX));
    _attributes.insert(std::make_pair("FFSR", _FFSR));
    _attributes.insert(std::make_pair("OUTMUX", _OUTMUX));
    _attributes.insert(std::make_pair("USED", _USED));
}

const std::string &QuarterSlicel::get_name() const {
    return _name;
}

void QuarterSlicel::set_name(const std::string &_name) {
    QuarterSlicel::_name = _name;
}


void QuarterSlicel::set_attribute(const std::string attr, const std::string val) {
    if(_attributes.find(attr) != _attributes.end()) {
        _attributes[attr] = val;
    }
    else {
        _attributes.insert(std::make_pair(attr, val));
    }
}


const std::string QuarterSlicel::get_attribute(std::string &attr) const {
    if(_attributes.find(attr) != _attributes.end()) {
        return _attributes.at(attr);
    }
    else {
        return "";
    }
}