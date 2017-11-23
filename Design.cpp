
#include "Design.h"
/*!
 *
 * @param _name
 * @param _device
 */
Design::Design(const std::string &_name, Device &_device): _name(_name), _device(_device) {
    _design_properties.insert(std::make_pair("PK_NGMTIMESTAMP", std::to_string(std::time(0))));
    _ncd_version = "v3.2";

}

/*!
 *
 * @param m
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

void Design::place() {
    for(auto itr_module = _modules.begin(); itr_module != _modules.end(); ++itr_module) {
        (*itr_module)->place(0, 0, _device);
    }
}
