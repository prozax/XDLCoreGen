
#include "PrimitiveSite.h"
#include "Tile.h"

/*!
 *
 * @param _name Name of the primitive site.
 * @param _type Type of the primitive site.
 * @param _pos_x X position of the primitive site.
 * @param _pos_y Y position of the primitive site.
 * @param _parent Pointer to the Tile containing this primitive site.
 */
PrimitiveSite::PrimitiveSite(const std::string &name, const std::string &type, int pos_x,
                             int pos_y, Tile* parent) : _name(name), _type(type), _pos_x(pos_x),
                                           _pos_y(pos_y), _parent(parent), _used(false) {}

std::ostream &operator<<(std::ostream &os, PrimitiveSite const &rhs) {
    os << "primitive_site ";
    os << rhs._name << " " << rhs._type << " @X" << rhs._pos_x << "Y" << rhs._pos_y;

    return os;
}
/*!
 *
 * @return Name of the primitive site.
 */
const std::string &PrimitiveSite::get_name() const {
    return _name;
}

/*!
 *
 * @param name New name of the primitive site.
 */
void PrimitiveSite::set_name(const std::string &name) {
    PrimitiveSite::_name = name;
}

/*!
 *
 * @return Type of the primitive site.
 */
const std::string &PrimitiveSite::get_type() const {
    return _type;
}

/*!
 *
 * @param type New type of the primitive site.
 */
void PrimitiveSite::set_type(const std::string &type) {
    PrimitiveSite::_type = type;
}
/*!
 *
 * @return X position of the primitive site.
 */
int PrimitiveSite::get_pos_x() const {
    return _pos_x;
}
/*!
 *
 * @param pos_x New X position of the primitive site.
 */
void PrimitiveSite::set_pos_x(int pos_x) {
    PrimitiveSite::_pos_x = pos_x;
}

/*!
 *
 * @return Y  position of the primitive site.
 */
int PrimitiveSite::get_pos_y() const {
    return _pos_y;
}

/*!
 *
 * @param pos_y New Y position of the primitive site.
 */
void PrimitiveSite::set_pos_y(int pos_y) {
    PrimitiveSite::_pos_y = pos_y;
}

/*!
 *
 * @return True if the primitive site is used, false if not.
 */
bool PrimitiveSite::is_used() const {
    return _used;
}

/*!
 *
 * @param used New used state of the primitive site.
 */
void PrimitiveSite::set_used(bool used) {
    PrimitiveSite::_used = used;
}

/*!
 *
 * @return Pointer to the Tile containing this primitive site.
 */
Tile *PrimitiveSite::get_parent() const {
    return _parent;
}

/*!
 *
 * @param parent Pointer to the new parent Tile.
 */
void PrimitiveSite::set_parent(Tile *parent) {
    PrimitiveSite::_parent = parent;
}
