#ifndef XDLGEN_SLICEL_H
#define XDLGEN_SLICEL_H

#include <string>
#include <iostream>
#include "QuarterSlicel.h"
#include "Slice.h"
#include "Tile.h"

class Slicel: public Slice {
private:
    static int _slicel_count;

    std::string _PRECYINIT;
    std::string _SRUSEDMUX;
    std::string _SYNC_ATTR;
    std::map<std::string, std::string> _attributes;

    QuarterSlicel _a;
    QuarterSlicel _b;
    QuarterSlicel _c;
    QuarterSlicel _d;

public:
    Slicel(const std::string &_name);

    //const std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, Slicel const& rhs);
    void set_attribute(std::string attr, std::string val);
};

#endif //XDLGEN_SLICEL_H
