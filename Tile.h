
#ifndef XDLCOREGEN_TILE_H
#define XDLCOREGEN_TILE_H


#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "PrimitiveSite.h"

//class PrimitiveSite;

class Tile {
protected:
    std::vector<PrimitiveSite*> _primitive_sites; /**< Primitve sites on this tile. */
    std::string _name; /**< Name of the tile. */
    std::string _type; /**< Type of the tile. */
    int _row; /**< Row of this tile. */
    int _column; /**< Column of this tile. */
    int _pos_x; /**< X position of this tile. */
    int _pos_y; /**< Y position of this tile. */

public:
    Tile(const std::string &_name, const std::string &_type, int _row, int _column, int _pos_x, int _pos_y);
    const std::string &get_type() const;
    void set_type(const std::string &_type);
    std::vector<PrimitiveSite*> &get_primitive_sites();
    void add_primitive_site(PrimitiveSite *);
    int get_row() const;
    void set_row(int _row);
    int get_column() const;
    void set_column(int _column);
    int get_pos_x() const;
    void set_pos_x(int _pos_x);
    int get_pos_y() const;
    void set_pos_y(int _pos_y);
    friend std::ostream& operator<<(std::ostream& os, Tile const& rhs);
    const std::string &get_name() const;
    void set_name(const std::string &_name);
};


#endif //XDLCOREGEN_TILE_H
