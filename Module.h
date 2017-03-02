
#ifndef XDLCOREGEN_MODULE_H
#define XDLCOREGEN_MODULE_H


#include <string>
#include <vector>
#include "Slicel.h"
#include "Net.h"
#include <math.h>
#include <sstream>

class Module {
protected:
    std::vector<Slicel> _slices;
    std::map<std::string, Net> _net;

public:
    Net* add_interconnect(std::string);
    Net* get_interconnect(std::string);
    const std::string to_string() const;
    const std::string get_net() const;
};


#endif //XDLCOREGEN_MODULE_H
