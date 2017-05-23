#include "QuarterSlicel.h"

const std::string QuarterSlicel::to_string() const {
    // TODO: make dynamic
    return _name + "5FFINIT::" +  _attributes.at("5FFINIT") + " " +
           _name + "5FFMUX::" + _attributes.at("5FFMUX") + " " +
           _name + "5FFSR::" + _attributes.at("5FFSR") + "\n       " +
           _name + "5LUT:" + _attributes.at("5LUTNAME") + ":#LUT:O5=" + _attributes.at("5LUT") + "\n       " +
           _name + "6LUT:" + _attributes.at("6LUTNAME") + ":#LUT:O6=" + _attributes.at("6LUT") + "\n       " +
           _name + "CY0::" + _attributes.at("CY0") + " " +
           _name + "FF::" + _attributes.at("FF") + " " +
           _name + "FFINIT::" + _attributes.at("FFINIT") + " " +
           _name + "FFMUX::" + _attributes.at("FFMUX") + " " +
           _name + "FFSR::" + _attributes.at("FFSR") + " " +
           _name + "OUTMUX::" + _attributes.at("OUTMUX") + " " +
           _name + "USED::" + _attributes.at("USED") + "\n       ";
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


std::string QuarterSlicel::get_attribute(const std::string &attr) {
    if(_attributes.find(attr) != _attributes.end()) {
        return _attributes[attr];
    }
    else {
        return "";
    }
}