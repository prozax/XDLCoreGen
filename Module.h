
#ifndef XDLCOREGEN_MODULE_H
#define XDLCOREGEN_MODULE_H


#include <string>
#include <vector>
#include "Slicel.h"
#include "Net.h"
#include "Port.h"
#include <math.h>
#include <sstream>
#include <deque>

class Module {
protected:
    std::string _name;
    std::string _inst_name;
    std::deque<Slicel> _slices;
    std::map<std::string, Net> _net;
    std::vector<Port> _ports;

public:
    Net* add_interconnect(std::string);
    Net* get_interconnect(std::string);
    void add_port(std::string, Slice&, std::string);
    const std::string to_string() const;
    const std::string get_net() const;
};


#endif //XDLCOREGEN_MODULE_H
