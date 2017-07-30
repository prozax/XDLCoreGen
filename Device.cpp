
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "Device.h"

Device::Device() : _column_count(0), _row_count(0){
    _name = "xc6vlx75tff484-3";
    std::string path = "devices/xc6vlx75tff484-3.xdl";
    std::ifstream df;
    std::string line;
    std::regex position_regex("X([0-9]+)Y([0-9]+)");
    std::smatch matches;
    //std::smatch matches;
    df.open(path);

    while (std::getline(df, line)) {
        if (line.at(0) != '#') {
            std::istringstream iss(line);
            std::string bracket, tmp, tmp2, name, type;
            char c;
            int row, column, primitive_site_count, pin_count;


            if (iss >> bracket >> row >> column >> name >> type >> primitive_site_count) {
                //                if (type.compare("CLBLM") == 0) {
                //                    clblm.insert(std::make_pair(std::make_tuple(1, 2), name));
                //                } else if (type.compare("CLBLL") == 0) {
                //                    clbll.insert(std::make_pair(std::make_tuple(3, 2), name));
                //                }
                //std::cout << name << " - " << row << " - " << column << std::endl;
                if (std::regex_search(name, matches, position_regex)) {
                    int y = std::stoi(matches[1]);
                    int x = std::stoi(matches[2]);
//                    std::cout << name << " - " << row << " - " << column << " - x" << x << "y" << y << std::endl;
                    Tile *new_tile = new Tile(name, type, row, column, x, y);


                    if(_row_count < row) _row_count = row;
                    if(_column_count < column) _column_count = column;

                    for(int n = 0; n < primitive_site_count; n++) {
                        if (std::getline(df, line)) {
                            std::istringstream iss(line);
                            if (iss >> bracket >> name >> type >> tmp >> tmp2 &&
                                std::regex_search(name, matches, position_regex)) {
                                int y = std::stoi(matches[1]);
                                int x = std::stoi(matches[2]);
                                //matches.clear();
                                //std::cout << name << " - x" << x << "y" << y << std::endl;
                                new_tile->add_primitive_site(new PrimitiveSite(name, type, x, y, new_tile));
                            }
                        }
                    }

                    _tiles.insert(std::make_pair(std::tuple<int, int>(column, row), *new_tile));
                }
            }
                //std::cout << type << " - " << name << std::endl;
        }
    }



    df.close();
}

std::ostream &operator<<(std::ostream &os, Device const &rhs) {
    os << "device " << rhs._name << std::endl;

    for(int i = 0; i <= rhs._column_count; i++)
        for(int j = 0; j <= rhs._row_count; j++)
            os << "\t" << rhs._tiles.at(std::tuple<int, int>(i, j)) << std::endl;

    return os;
}

const std::string &Device::get_name() const {
    return _name;
}

int Device::get_column_count() const {
    return _column_count;
}

int Device::get_row_count() const {
    return _row_count;
}

const std::map<std::tuple<int, int>, Tile> &Device::get_tiles() const {
    return _tiles;
}

PrimitiveSite* Device::get_next_primitive() {
    int last_row = _row_count;
    int last_column = _column_count;

    for(int i = last_column; i >= 0; i--) {
        for(int j = last_row; j >= 0; j--) {
            Tile t = _tiles.at(std::tuple<int, int>(i, j));

            for(auto p: t.get_primitive_sites()) {
                if (!p->is_used() && (p->get_type() == "SLICEL" || p->get_type() == "SLICEM")) {
                    return p;
                }
            }
        }
    }

    std::cout<<"No primitive site found.";
    return nullptr;
}
