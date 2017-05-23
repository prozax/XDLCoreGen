
#include "Port.h"

Port::Port(std::string _portname, Slice & _slice, std::string _slice_port): _portname(_portname), _slice(_slice), _slice_port(_slice_port) {
}

std::ostream &operator<<(std::ostream &os, Port const &rhs) {
    os << std::string("port \"") << rhs._portname << std::string("\" \"");
    os << rhs._slice.get_name() << std::string("\" \"");
    os << rhs._slice_port << std::string("\";");
    return os;
}
