
#include "Port.h"

Port::Port(std::string _portname, Slice & _slice, std::string _slice_port): _portname(_portname), _slice(_slice), _slice_port(_slice_port) {
}

std::ostream &operator<<(std::ostream &os, Port const &rhs) {
    os << "port \"" << rhs._portname << "\" \"";
    os << rhs._slice.get_name() << "\" \"";
    os << rhs._slice_port << "\";";
    return os;
}
