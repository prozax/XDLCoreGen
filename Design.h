
#ifndef XDLCOREGEN_DESIGN_H
#define XDLCOREGEN_DESIGN_H

#include <ctime>
#include <iostream>
#include <map>
#include "Module.h"
#include "Device.h"

class Design {
protected:
    std::string _name; /**< Design name. */
    Device _device; /**< Device instance for placing. */
    std::string _ncd_version; /**< NCD file version. */
    std::multimap<std::string, std::string> _design_properties; /**< Map of design properties. */
    std::vector<Module*> _modules; /**< Vector of modules in the design. */

public:
    explicit Design(Device &);
    Design(const std::string&, Device &);
    void add_module(Module&);
    void add_property(std::string prop, std::string value);
    friend std::ostream& operator<<(std::ostream& os, Design const& rhs);
    void place(int x_offset, int y_offset);
};


#endif //XDLCOREGEN_DESIGN_H
