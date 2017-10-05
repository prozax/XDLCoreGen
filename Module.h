
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
    std::string _name;
    std::string _inst_name;
    std::deque<Slicel> _slices;
    std::map<std::string, IOB> _pins;
    std::map<std::string, Net> _net;
    std::vector<Port> _ports;

public:
    std::deque<Slicel> &get_slices();
    Net* add_interconnect(std::string);
    Net* get_interconnect(std::string);
    void add_port(std::string, std::string, std::string);
    void add_port(std::string, Slice&, std::string);
    virtual void place(int x, int y, Device &device) = 0;
    friend std::ostream& operator<<(std::ostream& os, Module const& rhs);

    void add_ground_connection(const std::string instance_name, const std::string pin_name);

    void add_vcc_connection(const std::string instance_name, const std::string pin_name);
};


#endif //XDLCOREGEN_MODULE_H
