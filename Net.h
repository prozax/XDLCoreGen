
#ifndef XDLCOREGEN_NET_H
#define XDLCOREGEN_NET_H


#include <string>
#include <vector>
#include <map>
#include <sstream>

class Net {
protected:
    std::string _name;
public:
    Net(const std::string &_name);
    Net(const std::string &_name, const std::string &_type);

protected:
    std::string _type;
    std::multimap<std::string, std::string> _inpins;
    std::map<std::string, std::string> _outpin;

public:
    Net* set_outpin(std::string, std::string);
    Net* add_inpin(std::string, std::string);
    const std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, Net const& rhs);
    bool empty();
};


#endif //XDLCOREGEN_NET_H
