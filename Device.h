
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
    std::string _name; /**< Device name. */
    std::string _report_file_path; /**< Path to the device report file. */
    int _column_count; /**< Number of columns on the device. */
    int _row_count; /**< Number of rows on the device. */
    int _slice_row_count; /**< Number of rows with slices. */
    int _slice_column_count; /**< Number of columns with slices. */
    std::map<std::tuple<int, int>, Tile> _tiles; /**< Map of tiles. */
    std::map<std::tuple<int, int>, PrimitiveSite*> _slices; /**< Map of primitive sites on the device.*/

public:
    Device(std::string);
    friend std::ostream& operator<<(std::ostream& os, Device const& rhs);
    const std::string &get_name() const;
    int get_column_count() const;
    int get_row_count() const;
    int get_slice_row_count() const;
    int get_slice_column_count() const;
    const std::map<std::tuple<int, int>, Tile> &get_tiles() const;
    PrimitiveSite* get_next_primitive();
    PrimitiveSite *get_slice(int x, int y);
};

#endif //XDLCOREGEN_DEVICE_H
