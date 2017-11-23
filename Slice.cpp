#include "Slice.h"

const std::string &Slice::get_name() const {
    return _name;
}

void Slice::set_name(const std::string &n) {
    _name = n;
}

Slice::Slice(const std::string &_name) : _name(_name), _placed(false), _primitive_site(nullptr) {}

bool Slice::is_placed() const {
    return _placed;
}

void Slice::set_placed(bool placed) {
    Slice::_placed = placed;
}


PrimitiveSite *Slice::get_primitive_site() const {
    return _primitive_site;
}

void Slice::set_primitive_site(PrimitiveSite *_primitive_site) {
    Slice::_primitive_site = _primitive_site;
}

std::ostream &operator<<(std::ostream &os, Slice const &rhs) {
    os << "inst \"" << rhs._name << R"(" "SLICE", )";

    if(rhs.is_placed())
        os << "placed " << rhs._primitive_site->get_parent()->get_name() << " " << rhs._primitive_site->get_name() << ",\n";
    else
        os << "";

    os << "  cfg \" ";

    return os;
}
