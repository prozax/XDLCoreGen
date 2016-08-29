#ifndef XDLGEN_SLICEL_H
#define XDLGEN_SLICEL_H

#include <string>
#include "QuarterSlicel.h"

class Slicel {
private:
    std::string _name;
    std::string _PRECYINIT;
    std::string _SRUSEDMUX;
    std::string _SYNC_ATTR;
    QuarterSlicel* _a;
    QuarterSlicel* _b;
    QuarterSlicel* _c;
    QuarterSlicel* _d;

public:
    Slicel(const std::string &_name);

    const std::string to_string() const;
};


#endif //XDLGEN_SLICEL_H
