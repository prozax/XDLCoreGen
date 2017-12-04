
#include "Tile.h"

/*!
 * Constructor with all attributes.
 *
 * @param name Name of the tile.
 * @param type Type of the tile.
 * @param row Row of the tile.
 * @param column column of the tile.
 * @param pos_x X position of the tile.
 * @param pos_y Y position of the tile.
 */
Tile::Tile(const std::string &name, const std::string &type, int row, int column, int pos_x, int pos_y) : _name(name), _type(type),
                                                                                        _row(row), _column(column),
                                                                                        _pos_x(pos_x), _pos_y(pos_y) {}

/*!
 *
 * @return Type of the tile.
 */
const std::string &Tile::get_type() const {
    return _type;
}

/*!
 *
 * @param type New type of the tile.
 */
void Tile::set_type(const std::string &type) {
    Tile::_type = type;
}

/*!
 *
 * @return Vector of PrimitiveSites in the tile.
 */
std::vector<PrimitiveSite*> &Tile::get_primitive_sites() {
    return _primitive_sites;
}

/*!
 * Adds a PrimitiveSite to the tile.
 *
 * @param p Pointer to a PrimitiveSite.
 */
void Tile::add_primitive_site(PrimitiveSite *p) {
    _primitive_sites.push_back(p);
}

/*!
 *
 * @return Row of the tile.
 */
int Tile::get_row() const {
    return _row;
}

/*!
 *
 * @param row New row of the tile.
 */
void Tile::set_row(int row) {
    Tile::_row = row;
}

/*!
 *
 * @return Column of the tile.
 */
int Tile::get_column() const {
    return _column;
}

/*!
 *
 * @param column New column of the tile.
 */
void Tile::set_column(int column) {
    Tile::_column = column;
}

/*!
 *
 * @return X position of the tile.
 */
int Tile::get_pos_x() const {
    return _pos_x;
}

/*!
 *
 * @param pos_x New X position of the tile.
 */
void Tile::set_pos_x(int pos_x) {
    Tile::_pos_x = pos_x;
}

/*!
 *
 * @return Y position of the tile.
 */
int Tile::get_pos_y() const {
    return _pos_y;
}

/*!
 *
 * @param pos_y New Y position of the tile.
 */
void Tile::set_pos_y(int pos_y) {
    Tile::_pos_y = pos_y;
}

/*!
 *
 * @return Name of the tile.
 */
const std::string &Tile::get_name() const {
    return _name;
}

/*!
 *
 * @param name New name of the tile.
 */
void Tile::set_name(const std::string &name) {
    Tile::_name = name;
}

std::ostream &operator<<(std::ostream &os, Tile const &rhs) {
    os << "tile " << rhs._name << " " << rhs._type << " @row" << rhs._row << "column" << rhs._column;
    os << " @X" << rhs._pos_x << "Y" << rhs._pos_y << std::endl;

    for(auto p: rhs._primitive_sites) {
        os << "\t" << p << std::endl;
    }

    return os;
}