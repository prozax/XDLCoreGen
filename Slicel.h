#ifndef XDLGEN_SLICEL_H
#define XDLGEN_SLICEL_H

#include <string>
#include <iostream>
#include "QuarterSlicel.h"
#include "Slice.h"
#include "Tile.h"

class Slicel: public Slice {
private:
    QuarterSlicel _a; /**< A LUTs and registers. */
    QuarterSlicel _b; /**< B LUTs and registers. */
    QuarterSlicel _c; /**< C LUTs and registers. */
    QuarterSlicel _d; /**< D LUTs and registers. */

public:
    Slicel(const std::string &_name);
    friend std::ostream& operator<<(std::ostream& os, Slicel const& rhs);
    void set_attribute(std::string attr, std::string val);
    const std::string get_attribute(std::string attr) const;
};

#endif //XDLGEN_SLICEL_H
