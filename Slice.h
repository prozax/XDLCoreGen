#ifndef XDLGEN_SLICE_H
#define XDLGEN_SLICE_H


#include <string>

class Slice {

public:
    virtual const std::string to_string() const {
        return std::string();
    }

};


#endif //XDLGEN_SLICE_H
