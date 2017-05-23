#ifndef XDLGEN_SLICE_H
#define XDLGEN_SLICE_H


#include <string>

class Slice {
protected:
    std::string _name;
public:
    Slice(const std::string &_name);

public:


public:
    virtual const std::string to_string() const {
        return std::string();
    }

    void set_name(const std::string &_name);
    const std::string &get_name() const;
};


#endif //XDLGEN_SLICE_H
