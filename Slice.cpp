#include "Slice.h"

/*!
 * Constructor for an unplaced Slice.
 *
 * @param name Name of the slice.
 */
Slice::Slice(const std::string &name) : _name(name), _placed(false), _primitive_site(nullptr) {}

/*!
 *
 * @return Name of the slice.
 */
const std::string &Slice::get_name() const {
    return _name;
}

/*!
 *
 * @param n New name of the slice.
 */
void Slice::set_name(const std::string &n) {
    _name = n;
}

/*!
 *
 * @return True if the slice has a PrimitiveSite, false if not.
 */
bool Slice::is_placed() const {
    return _placed;
}

/*!
 *
 * @param placed New placement status of the slice.
 */
void Slice::set_placed(bool placed) {
    Slice::_placed = placed;
}

/*!
 *
 * @return Pointer to the PrimitiveSite the slice is currently placed on.
 */
PrimitiveSite *Slice::get_primitive_site() const {
    return _primitive_site;
}

/*!
 *
 * @param primitive_site Pointer to the new PrimitiveSite the Slice is placed on.
 */
void Slice::set_primitive_site(PrimitiveSite *primitive_site) {
    Slice::_primitive_site = primitive_site;
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
