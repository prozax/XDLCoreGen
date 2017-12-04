
#ifndef XDLCOREGEN_PORT_H
#define XDLCOREGEN_PORT_H


#include "Slice.h"
#include "Pin.h"
#include <iostream>

class Port {
protected:
    std::string _port_name; /**< Name of the port. */
    Pin _pin; /**< Pin connected to the port. */

public:
    Port(std::string, std::string, std::string);
    friend std::ostream& operator<<(std::ostream& os, Port const& rhs);
};


#endif //XDLCOREGEN_PORT_H
