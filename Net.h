
#ifndef XDLCOREGEN_NET_H
#define XDLCOREGEN_NET_H


#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <tuple>
#include "Pin.h"

class Net {
protected:
    std::string _name;
    std::string _type;
    std::vector<Pin> _inpins;
    Pin _outpin;

public:
    Net(const std::string &_name);
    Net(const std::string &_name, const std::string &_type);
    Net* set_outpin(std::string, std::string);
    const std::string &get_name() const;
    const std::string &get_type() const;
    const std::vector<Pin> &get_inpins() const;
    Pin &get_outpin();
    Net* add_inpin(std::string, std::string);
    friend std::ostream& operator<<(std::ostream& os, Net const& rhs);
    bool empty();
};


#endif //XDLCOREGEN_NET_H
