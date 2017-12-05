
#include "Port.h"

#include <utility>

/*!
 * @brief Constructor with instance name and pin name.
 *
 * @param portname Name of the port.
 * @param ps_name Name of the instance of the PrimitiveSite the port is connected to.
 * @param pin Name of the Pin on the PrimitiveSite the port is connected to.
 */
Port::Port(std::string portname, std::string ps_name, std::string pin): _port_name(std::move(portname)), _pin(
        std::move(ps_name), std::move(pin)) {}

std::ostream &operator<<(std::ostream &os, Port const &rhs) {
    os << "port \"" << rhs._port_name << "\" \"";
    os << rhs._pin.get_instance() << "\" \"";
    os << rhs._pin.get_pin() << "\";";
    return os;
}
