#include "Slicel.h"

Slicel::Slicel(const std::string &_name): _name(_name) {
    _a = new QuarterSlicel("A");
    _b = new QuarterSlicel("B");
    _c = new QuarterSlicel("C");
    _d = new QuarterSlicel("D");

    _PRECYINIT = "#OFF";
    _SRUSEDMUX = "#OFF";
    _SYNC_ATTR = "#OFF";
}

const std::string Slicel::to_string() const {
    return "inst \"" + _name + "\" \"SLICEL\", unplaced,\n" +
           "  cfg \" " +
           _a->to_string() + "       " +
           _b->to_string() + "       " +
           _c->to_string() + "       " +
           _d->to_string() + "       " +
           "PRECYINIT::" + _PRECYINIT + " " +
           "SRUSEDMUX::" + _SRUSEDMUX + " " +
           "SYNC_ATTR::" + _SYNC_ATTR + " \";";
}



