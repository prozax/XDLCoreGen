
#ifndef XDLCOREGEN_PORT_H
#define XDLCOREGEN_PORT_H


#include "Slice.h"
#include "Pin.h"
#include <iostream>

class Port {
protected:
    //Slice& _slice;
    std::string _port_name;
    Pin _pin;

public:
    Port(std::string, std::string, std::string);
    friend std::ostream& operator<<(std::ostream& os, Port const& rhs);
};


#endif //XDLCOREGEN_PORT_H
