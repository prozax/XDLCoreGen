#include "QuarterSlicel.h"

const std::string QuarterSlicel::to_string() const {
    return _name + "5FFINIT::" + _5FFINIT + " " +
           _name + "5FFMUX::" + _5FFMUX + " " +
           _name + "5FFSR::" + _5FFSR + " " +
           _name + "5LUT:" + _5LUTNAME + ":" + _5LUT + " " +
           _name + "6LUT:" + _6LUTNAME + ":" + _6LUT + " " +
           _name + "CY0::" + _CY0 + "\n       " +
           _name + "FF::" + _FF + " " +
           _name + "FFINIT::" + _FFINIT + " " +
           _name + "FFMUX::" + _FFMUX + " " +
           _name + "FFSR::" + _FFSR + " " +
           _name + "OUTMUX::" + _OUTMUX + " " +
           _name + "USED::" + _USED + " \n";
}

QuarterSlicel::QuarterSlicel(const std::string &_name): _name(_name) {
    _5FFINIT = "#OFF";
    _5FFMUX = "#OFF";
    _5FFSR = "#OFF";
    _5LUT = "#OFF";
    _5LUTNAME = "";
    _6LUT = "#OFF";
    _6LUTNAME = "";
    _CY0 = "#OFF";
    _FF = "#OFF";
    _FFINIT = "#OFF";
    _FFMUX = "#OFF";
    _FFSR = "#OFF";
    _OUTMUX = "#OFF";
    _USED = "#OFF";
}

QuarterSlicel::QuarterSlicel(const std::string &_name, const std::string &_5FFINIT, const std::string &_5FFMUX,
                             const std::string &_5FFSR, const std::string &_5LUT, const std::string &_5LUTNAME,
                             const std::string &_6LUT, const std::string &_6LUTNAME, const std::string &_CY0,
                             const std::string &_FF, const std::string &_FFINIT, const std::string &_FFMUX,
                             const std::string &_FFSR, const std::string &_OUTMUX, const std::string &_USED)
        : _name(_name),
          _5FFINIT(_5FFINIT),
          _5FFMUX(_5FFMUX),
          _5FFSR(_5FFSR),
          _5LUT(_5LUT),
          _5LUTNAME(_5LUTNAME),
          _6LUT(_6LUT),
          _6LUTNAME(_6LUTNAME),
          _CY0(_CY0),
          _FF(_FF),
          _FFINIT(_FFINIT),
          _FFMUX(_FFMUX),
          _FFSR(_FFSR),
          _OUTMUX(_OUTMUX),
          _USED(_USED) { }

const std::string &QuarterSlicel::get_name() const {
    return _name;
}

void QuarterSlicel::set_name(const std::string &_name) {
    QuarterSlicel::_name = _name;
}

const std::string &QuarterSlicel::get_5FFINIT() const {
    return _5FFINIT;
}

void QuarterSlicel::set_5FFINIT(const std::string &_5FFINIT) {
    QuarterSlicel::_5FFINIT = _5FFINIT;
}

const std::string &QuarterSlicel::get_5FFMUX() const {
    return _5FFMUX;
}

void QuarterSlicel::set_5FFMUX(const std::string &_5FFMUX) {
    QuarterSlicel::_5FFMUX = _5FFMUX;
}

const std::string &QuarterSlicel::get_5FFSR() const {
    return _5FFSR;
}

void QuarterSlicel::set_5FFSR(const std::string &_5FFSR) {
    QuarterSlicel::_5FFSR = _5FFSR;
}

const std::string &QuarterSlicel::get_5LUT() const {
    return _5LUT;
}

void QuarterSlicel::set_5LUT(const std::string &_5LUT) {
    QuarterSlicel::_5LUT = _5LUT;
}

const std::string &QuarterSlicel::get_5LUTNAME() const {
    return _5LUTNAME;
}

void QuarterSlicel::set_5LUTNAME(const std::string &_5LUTNAME) {
    QuarterSlicel::_5LUTNAME = _5LUTNAME;
}

const std::string &QuarterSlicel::get_6LUT() const {
    return _6LUT;
}

void QuarterSlicel::set_6LUT(const std::string &_6LUT) {
    QuarterSlicel::_6LUT = _6LUT;
}

const std::string &QuarterSlicel::get_6LUTNAME() const {
    return _6LUTNAME;
}

void QuarterSlicel::set_6LUTNAME(const std::string &_6LUTNAME) {
    QuarterSlicel::_6LUTNAME = _6LUTNAME;
}

const std::string &QuarterSlicel::get_CY0() const {
    return _CY0;
}

void QuarterSlicel::set_CY0(const std::string &_CY0) {
    QuarterSlicel::_CY0 = _CY0;
}

const std::string &QuarterSlicel::get_FF() const {
    return _FF;
}

void QuarterSlicel::set_FF(const std::string &_FF) {
    QuarterSlicel::_FF = _FF;
}

const std::string &QuarterSlicel::get_FFINIT() const {
    return _FFINIT;
}

void QuarterSlicel::set_FFINIT(const std::string &_FFINIT) {
    QuarterSlicel::_FFINIT = _FFINIT;
}

const std::string &QuarterSlicel::get_FFMUX() const {
    return _FFMUX;
}

void QuarterSlicel::set_FFMUX(const std::string &_FFMUX) {
    QuarterSlicel::_FFMUX = _FFMUX;
}

const std::string &QuarterSlicel::get_FFSR() const {
    return _FFSR;
}

void QuarterSlicel::set_FFSR(const std::string &_FFSR) {
    QuarterSlicel::_FFSR = _FFSR;
}

const std::string &QuarterSlicel::get_OUTMUX() const {
    return _OUTMUX;
}

void QuarterSlicel::set_OUTMUX(const std::string &_OUTMUX) {
    QuarterSlicel::_OUTMUX = _OUTMUX;
}

const std::string &QuarterSlicel::get_USED() const {
    return _USED;
}

void QuarterSlicel::set_USED(const std::string &_USED) {
    QuarterSlicel::_USED = _USED;
}