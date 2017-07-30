
#include "PrimitiveSite.h"
#include "Tile.h"

PrimitiveSite::PrimitiveSite(const std::string &_name, const std::string &_type, int _pos_x,
                             int _pos_y, Tile* _parent) : _name(_name), _type(_type), _pos_x(_pos_x),
                                           _pos_y(_pos_y), _parent(_parent), _used(false) {}

std::ostream &operator<<(std::ostream &os, PrimitiveSite const &rhs) {
    os << "primitive_site ";
    os << rhs._name << " " << rhs._type << " @X" << rhs._pos_x << "Y" << rhs._pos_y;

    return os;
}

const std::string &PrimitiveSite::get_name() const {
    return _name;
}

void PrimitiveSite::set_name(const std::string &_name) {
    PrimitiveSite::_name = _name;
}

const std::string &PrimitiveSite::get_type() const {
    return _type;
}

void PrimitiveSite::set_type(const std::string &_type) {
    PrimitiveSite::_type = _type;
}

int PrimitiveSite::get_pos_x() const {
    return _pos_x;
}

void PrimitiveSite::set_pos_x(int _pos_x) {
    PrimitiveSite::_pos_x = _pos_x;
}

int PrimitiveSite::get_pos_y() const {
    return _pos_y;
}

void PrimitiveSite::set_pos_y(int _pos_y) {
    PrimitiveSite::_pos_y = _pos_y;
}

bool PrimitiveSite::is_used() const {
    return _used;
}

void PrimitiveSite::set_used(bool _used) {
    PrimitiveSite::_used = _used;
}

Tile *PrimitiveSite::get_parent() const {
    return _parent;
}

void PrimitiveSite::set_parent(Tile *_parent) {
    PrimitiveSite::_parent = _parent;
}
