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

    QuarterSlicel _a;
    QuarterSlicel _b;
    QuarterSlicel _c;
    QuarterSlicel _d;

public:
    Slicel(const std::string &_name);

    friend std::ostream& operator<<(std::ostream& os, Slicel const& rhs);
    void set_attribute(std::string attr, std::string val);
    const std::string get_attribute(std::string attr) const;
};

#endif //XDLGEN_SLICEL_H
