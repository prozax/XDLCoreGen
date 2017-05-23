#ifndef XDLGEN_SLICEL_H
#define XDLGEN_SLICEL_H

#include <string>
#include "QuarterSlicel.h"
#include "Slice.h"

class Slicel: public Slice {
private:
    static int slicel_count;

private:
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

    const std::string to_string() const;
    void set_attribute(std::string attr, std::string val);
};

#endif //XDLGEN_SLICEL_H
