
#ifndef XDLCOREGEN_NET_H
#define XDLCOREGEN_NET_H


#include <string>
#include <vector>
#include <map>
#include <sstream>

class Net {
protected:
    std::map<std::string, std::string> _inpins;
    std::map<std::string, std::string> _outpin;

public:
    Net* set_outpin(std::string, std::string);
    Net* add_inpin(std::string, std::string);
    const std::string to_string() const;
    bool empty();
};


#endif //XDLCOREGEN_NET_H
