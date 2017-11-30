
#include "Design.h"
/*!
 * Constructor for custom naming.
 *
 * @param name Name of the design.
 * @param device Device instance to place the design onto.
 */
Design::Design(const std::string &name, Device &device): _name(name), _device(device) {
    add_property("PK_NGMTIMESTAMP", std::to_string(std::time(0)));
    _ncd_version = "v3.2";

}

/*!
 * Constructor for hard macros.
 *
 * @param device Device instance to place the design onto.
 */
Design::Design(Device & device): Design("__XILINX_NMC_MACRO", device) {}

/*!
 * Adds a Module instance to this design.
 *
 * @param m Module instance to be added to the design.
 */
void Design::add_module(Module &m) {
    _modules.push_back(&m);
}

std::ostream &operator<<(std::ostream &os, Design const &rhs) {
    os<<"design \"";
    os<<rhs._name;
    os<<"\" ";
    os<<rhs._device.get_name();
    os<<" ";
    os<<rhs._ncd_version;
    os<<","<<std::endl;
    os<<"cfg \"";
    os<<std::endl;

    for(auto const& i: rhs._design_properties) {
        os << "_DESIGN_PROP::";
        os << i.first << ":" << i.second << std::endl;
    }

    os<<"\";"<<std::endl<<std::endl;


    for(auto i: rhs._modules) {
        os << *i << std::endl;
    }

    return os;
}

/*!
 * Calls the place method of every Module in the design.
 *
 * @param x_offset X position offset on the Device for the design.
 * @param y_offset Y position offset on the Device for the design.
 */
void Design::place(int x_offset, int y_offset) {
    for(auto itr_module = _modules.begin(); itr_module != _modules.end(); ++itr_module) {
        (*itr_module)->place(x_offset, y_offset, _device);
    }
}

/*!
 * Sets the value of a design property or adds it if it doesn't exist.
 *
 * @param prop Property name.
 * @param value Property Value
 */
void Design::add_property(std::string prop, std::string value) {
    _design_properties.emplace(prop, value);
}
