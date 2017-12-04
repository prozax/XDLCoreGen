
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "Device.h"

/*!
 * This constructor takes a file path and parses the file for the device name and all primitive sites
 * on the device.
 *
 * @return Path to a device report file.
 */
Device::Device(std::string path) : _column_count(0), _row_count(0), _slice_row_count(0),
                                                      _slice_column_count(0), _name(""), _report_file_path(path){
    std::ifstream df;
    std::string line;
    std::regex position_regex("X([0-9]+)Y([0-9]+)");
    std::smatch matches;
    bool header_done = false;
    df.open(_report_file_path);


    while (std::getline(df, line)) {
        if (line.at(0) != '#') {
            std::istringstream iss(line);
            std::string bracket, tmp, tmp2, name, type, device_name;
            int row, column, primitive_site_count;

            if(!header_done && iss >> bracket >> tmp >> device_name >> tmp2) {
                _name = device_name;
                header_done = true;
            }

            if (iss >> bracket >> row >> column >> name >> type >> primitive_site_count
                && std::regex_search(name, matches, position_regex)) {
                int x_tile = std::stoi(matches[1]);
                int y_tile = std::stoi(matches[2]);
                auto *new_tile = new Tile(name, type, row, column, x_tile, y_tile);

                if(_row_count < row) _row_count = row;
                if(_column_count < column) _column_count = column;

                for(int n = 0; n < primitive_site_count; n++) {
                    if (std::getline(df, line)) {
                        std::istringstream iss(line);
                        if (iss >> bracket >> name >> type >> tmp >> tmp2 &&
                                std::regex_search(name, matches, position_regex)) {
                            int x_primitive = std::stoi(matches[1]);
                            int y_primitive = std::stoi(matches[2]);

                            auto *pm = new PrimitiveSite(name, type, x_primitive, y_primitive, new_tile);
                            new_tile->add_primitive_site(pm);

                            // saving slices separately
                            if(type == "SLICEL" || type == "SLICEM") {
                                if(_slice_column_count < x_primitive) _slice_column_count = x_primitive;
                                if(_slice_row_count < y_primitive) _slice_row_count = y_primitive;

                                _slices.emplace(std::tuple<int, int>(x_primitive, y_primitive), pm);
                            }
                        }
                    }
                }

                _tiles.emplace(std::tuple<int, int>(column, row), *new_tile);
            }
        }
    }

    // adding one to the counts because the actual positions used above start at 0
    if(_row_count > 0) _row_count++;
    if(_column_count > 0) _column_count++;
    if(_slice_row_count > 0) _slice_row_count++;
    if(_slice_column_count > 0) _slice_column_count++;

    df.close();
}

std::ostream &operator<<(std::ostream &os, Device const &rhs) {
    os << "device " << rhs._name << std::endl;

    for(int i = 0; i <= rhs._column_count; i++)
        for(int j = 0; j <= rhs._row_count; j++)
            os << "\t" << rhs._tiles.at(std::tuple<int, int>(i, j)) << std::endl;

    return os;
}

/*!
 * Returns the device name.
 *
 * @return Device name.
 */
const std::string &Device::get_name() const {
    return _name;
}

/*!
 * Returns the total column count of the device.
 *
 * @return Column count.
 */
int Device::get_column_count() const {
    return _column_count;
}

/*!
 * Returns the total row count of the device.
 *
 * @return Row count.
 */
int Device::get_row_count() const {
    return _row_count;
}

/*!
 * Returns a map of all tiles.
 *
 * @return Map of tiles.
 */

const std::map<std::tuple<int, int>, Tile> &Device::get_tiles() const {
    return _tiles;
}

/*!
 * Returns a pointer to the slice at the given coordinates or nullptr if it doesn't exist.
 *
 * @param x X coordinate of the slice.
 * @param y Y coordinate of the slice.
 * @return Pointer to slice at x/y or nullptr.
 */
PrimitiveSite* Device::get_slice(int x, int y) {
    if(_slices.count(std::tuple<int, int>(x, y)) > 0) {
        return _slices.at(std::tuple<int, int>(x, y));
    }

    return nullptr;
}

/*!
 * Returns the number of rows that contain slices on the device.
 *
 * @return Number of rows that contain slices of this device.
 */
int Device::get_slice_row_count() const {
    return _slice_row_count;
}

/*!
 * Returns the number of columns that contain slices on the device.
 *
 * @return Number of columns that contain slices of this device.
 */
int Device::get_slice_column_count() const {
    return _slice_column_count;
}
