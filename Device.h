
#ifndef XDLCOREGEN_DEVICE_H
#define XDLCOREGEN_DEVICE_H

#include <map>
#include <tuple>
#include <vector>
#include <iostream>
#include "Slicem.h"
#include "Slicel.h"
#include "Tile.h"
#include "PrimitiveSite.h"

class Device {
protected:
    std::string _name;
    int _column_count;
    int _row_count;
    //std::vector<Tile> _tiles;
    std::map<std::tuple<int, int>, Tile> _tiles;

public:
    Device();
    friend std::ostream& operator<<(std::ostream& os, Device const& rhs);
    const std::string &get_name() const;
    int get_column_count() const;
    int get_row_count() const;
    const std::map<std::tuple<int, int>, Tile> &get_tiles() const;
    PrimitiveSite* get_next_primitive();
};

#endif //XDLCOREGEN_DEVICE_H
