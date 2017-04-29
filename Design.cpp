
#include "Design.h"

Design::Design(const std::string &_name, const std::string &_device): _name(_name), _device(_device) {
    _design_properties.insert(std::make_pair("PK_NGMTIMESTAMP", std::to_string(std::time(0))));
    _ncd_version = "v3.2";

}

void Design::add_module(Module m) {
    _modules.push_back(m);
}

const std::string Design::to_string() const {
    std::stringstream ret;

    ret<<"design \"";
    ret<<_name;
    ret<<"\" ";
    ret<<_device;
    ret<<" ";
    ret<<_ncd_version;
    ret<<","<<std::endl;
    ret<<"cfg \"";
    ret<<std::endl;

    for(auto const& i: _design_properties) {
        ret << "_DESIGN_PROP::";
        ret << i.first << ":" << i.second << std::endl;
    }

    ret<<"\";"<<std::endl<<std::endl;


    for(auto i: _modules) {
        ret<<i.to_string();
    }

    return ret.str();
}
