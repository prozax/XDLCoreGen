
#ifndef XDLCOREGEN_DESIGN_H
#define XDLCOREGEN_DESIGN_H

#include <ctime>
#include <iostream>
#include <map>
#include "Module.h"
#include "Device.h"

class Design {
protected:
    std::string _name;
    Device _device;
    std::time_t _timestamp;
    std::string _ncd_version;
    std::multimap<std::string, std::string> _design_properties;
    std::vector<Module*> _modules;

public:
    Design(Device &);
    Design(const std::string&, Device &);

    void add_module(Module&);
    friend std::ostream& operator<<(std::ostream& os, Design const& rhs);
    void place();
};


#endif //XDLCOREGEN_DESIGN_H
