
#include "Tile.h"
//#include "PrimitiveSite.h"

Tile::Tile(const std::string &_name, const std::string &_type, int _row, int _column, int _pos_x, int _pos_y) : _name(_name), _type(_type),
                                                                                        _row(_row), _column(_column),
                                                                                        _pos_x(_pos_x), _pos_y(_pos_y) {}
const std::string &Tile::get_type() const {
    return _type;
}

void Tile::set_type(const std::string &_type) {
    Tile::_type = _type;
}

std::vector<PrimitiveSite*> &Tile::get_primitive_sites() {
    return _primitive_sites;
}

void Tile::add_primitive_site(PrimitiveSite *p) {
    _primitive_sites.push_back(p);
}


int Tile::get_row() const {
    return _row;
}

void Tile::set_row(int _row) {
    Tile::_row = _row;
}

int Tile::get_column() const {
    return _column;
}

void Tile::set_column(int _column) {
    Tile::_column = _column;
}

int Tile::get_pos_x() const {
    return _pos_x;
}

void Tile::set_pos_x(int _pos_x) {
    Tile::_pos_x = _pos_x;
}

int Tile::get_pos_y() const {
    return _pos_y;
}

void Tile::set_pos_y(int _pos_y) {
    Tile::_pos_y = _pos_y;
}

std::ostream &operator<<(std::ostream &os, Tile const &rhs) {
    os << "tile " << rhs._name << " " << rhs._type << " @row" << rhs._row << "column" << rhs._column;
    os << " @X" << rhs._pos_x << "Y" << rhs._pos_y << std::endl;

    for(auto p: rhs._primitive_sites) {
        os << "\t" << p << std::endl;
    }

    return os;
}

const std::string &Tile::get_name() const {
    return _name;
}

void Tile::set_name(const std::string &_name) {
    Tile::_name = _name;
}
