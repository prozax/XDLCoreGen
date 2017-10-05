
#include "Port.h"

Port::Port(std::string _portname, std::string _slice_name, std::string _pin): _port_name(_portname), _pin(_slice_name, _pin) {
}

std::ostream &operator<<(std::ostream &os, Port const &rhs) {
    os << "port \"" << rhs._port_name << "\" \"";
    os << rhs._pin.get_instance() << "\" \"";
    os << rhs._pin.get_pin() << "\";";
    return os;
}
