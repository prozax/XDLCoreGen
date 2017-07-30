
#ifndef XDLCOREGEN_PORT_H
#define XDLCOREGEN_PORT_H


#include "Slice.h"
#include <iostream>

class Port {
protected:
    Slice& _slice;
    std::string _portname;
    std::string _slice_port;

public:
    Port(std::string, Slice&, std::string);
    friend std::ostream& operator<<(std::ostream& os, Port const& rhs);
};


#endif //XDLCOREGEN_PORT_H
