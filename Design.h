
#ifndef XDLCOREGEN_DESIGN_H
#define XDLCOREGEN_DESIGN_H

#include <ctime>
#include <iostream>
#include <map>
#include "Module.h"

class Design {
protected:
    std::string _name;
    std::string _device;
    std::time_t _timestamp;
    std::string _ncd_version;
    std::multimap<std::string, std::string> _design_properties;
    std::vector<Module> _modules;

public:
    Design(const std::string&, const std::string&);

    void add_module(Module);
    const std::string to_string() const;
};


#endif //XDLCOREGEN_DESIGN_H
