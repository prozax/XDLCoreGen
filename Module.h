
#ifndef XDLCOREGEN_MODULE_H
#define XDLCOREGEN_MODULE_H


#include <string>
#include <vector>
#include "Slicel.h"
#include "Net.h"
#include "Port.h"
#include "Device.h"
#include "IOB.h"
#include <math.h>
#include <sstream>
#include <deque>
#include <iostream>

class Module {
protected:
    std::string _name; /**< Name of the module. */
    std::string _inst_name; /**< Instance name of the reference PrimitiveSite. */
    std::deque<Slicel> _slices; /**< List of Slicel. */
    std::map<std::string, IOB> _pins; /**< Map of IOBs. */
    std::map<std::string, Net> _net; /**< Map of Nets. */
    std::vector<Port> _ports; /**< Vector of Ports. */

public:
    Module();
    Module(std::string);

    void add_slice(Slicel);
    std::deque<Slicel> &get_slices();
    Net* add_interconnect(std::string);

    void add_port(std::string, std::string, std::string);
    void add_port(std::string, Slice&, std::string);
    virtual void place(int x, int y, Device &device);
    friend std::ostream& operator<<(std::ostream& os, Module const& rhs);
    void add_ground_connection(std::string instance_name, std::string pin_name);
    void add_vcc_connection(std::string instance_name, std::string pin_name);
};


#endif //XDLCOREGEN_MODULE_H
