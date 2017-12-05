
#include "Net.h"
/*!
 * @brief Constructor for a regular interconnection net.
 *
 * @param name Name of the net.
 */
Net::Net(const std::string &name) : _name(name), _type(""), _outpin(Pin("", "")) {}

/*!
 * @brief Constructor with type parameter.
 * The type can be "gnd" or "vcc" for a power net or empty string for a regular net.
 * Power nets are not supported for hard macros, use regular nets with a port instead.
 *
 * @param name Name of the net.
 * @param type Type of the net.
 */
Net::Net(const std::string &name, const std::string &type) : _name(name), _type(type), _outpin(Pin("", "")) {}

/*!
 * @brief Sets the outpin of the net.
 *
 * @param instance Name of the Slice to connect.
 * @param pin Name of the Pin on the Slice.
 * @return A pointer to the Net.
 */
Net* Net::set_outpin(std::string instance, std::string pin) {
    _outpin = Pin(instance, pin);
    return this;
}

/*!
 * @brief Creates an inpin in the net.
 *
 * @param instance Name of the Slice to connect.
 * @param pin Name of the Pin on the Slice.
 * @return A pointer to the Net.
 */
Net* Net::add_inpin(std::string instance, std::string pin) {
    _inpins.emplace_back(instance, pin);
    return this;
}

/*!
 *
 * @return True if the net contains no inpins and no outpins. False if at least one inpin or outpin exists.
 */
bool Net::empty() {
    return _outpin.empty() && _inpins.empty();
}

/*!
 *
 * @return Name of the net.
 */
const std::string &Net::get_name() const {
    return _name;
}

/*!
 *
 * @return Type of the net (gnd, vcc or empty string for regular net).
 */
const std::string &Net::get_type() const {
    return _type;
}

/*!
 *
 * @return Vector of all inpins in the net.
 */
const std::vector<Pin> &Net::get_inpins() const {
    return _inpins;
}

/*!
 *
 * @return The outpin of the net.
 */
Pin &Net::get_outpin() {
    return _outpin;
}

std::ostream &operator<<(std::ostream &os, Net const &rhs) {
    os << "net \"";

    os << rhs._name << "\" " << "," << std::endl;

    if(!rhs._outpin.empty()) {
        os << "    " << "outpin \"";
        os << rhs._outpin.get_instance() << "\" " << rhs._outpin.get_pin() << " ," << std::endl;
    }

    for(const Pin& i: rhs._inpins) {
        os << "    " << "inpin \"";
        os << i.get_instance() << "\" " << i.get_pin() << " ," << std::endl;
    }

    os << ";" << std::endl;

    return os;
}
