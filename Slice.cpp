#include "Slice.h"

const std::string &Slice::get_name() const {
    return _name;
}

void Slice::set_name(const std::string &n) {
    _name = n;
}

Slice::Slice(const std::string &_name) : _name(_name), _placed(false), _pos_y(0), _pos_x(0), _primitive_site(nullptr) {}

bool Slice::isPlaced() const {
    return _placed;
}

void Slice::setPlaced(bool placed) {
    Slice::_placed = placed;
}

int Slice::getPos_x() const {
    return _pos_x;
}

void Slice::setPos_x(int pos_x) {
    Slice::_pos_x = pos_x;
}

int Slice::getPos_y() const {
    return _pos_y;
}

void Slice::setPos_y(int pos_y) {
    Slice::_pos_y = pos_y;
}

PrimitiveSite *Slice::get_primitive_site() const {
    return _primitive_site;
}

void Slice::set_primitive_site(PrimitiveSite *_primitive_site) {
    Slice::_primitive_site = _primitive_site;
}

std::ostream &operator<<(std::ostream &os, Slice const &rhs) {
    os << "port \"" << rhs._name << "\" \"SLICE\", ";

    if(rhs.isPlaced())
        os << "placed " << rhs._primitive_site->get_parent()->get_name() << " " << rhs._primitive_site->get_name() << ",\n";
    else
        os << "";

    os << "  cfg \" ";

    return os;
}
