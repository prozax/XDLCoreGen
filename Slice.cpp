#include "Slice.h"

const std::string &Slice::get_name() const {
    return _name;
}

void Slice::set_name(const std::string &n) {
    _name = n;
}

Slice::Slice(const std::string &_name) : _name(_name) {}
