#include "QuarterSlicel.h"

/*!
 * Constructor creating a QuarterSlice with all features deactivated.
 *
 * @param name Name of the quarter slice.
 */
QuarterSlicel::QuarterSlicel(const std::string &name): _name(name) {
    _attributes.insert(std::make_pair("5FFINIT", "#OFF"));
    _attributes.insert(std::make_pair("5FFMUX", "#OFF"));
    _attributes.insert(std::make_pair("5FFSR", "#OFF"));
    _attributes.insert(std::make_pair("5LUT", "#OFF"));
    _attributes.insert(std::make_pair("5LUTNAME", ""));
    _attributes.insert(std::make_pair("6LUT", "#OFF"));
    _attributes.insert(std::make_pair("6LUTNAME", ""));
    _attributes.insert(std::make_pair("CY0", "#OFF"));
    _attributes.insert(std::make_pair("FF", "#OFF"));
    _attributes.insert(std::make_pair("FFNAME", ""));
    _attributes.insert(std::make_pair("FFINIT", "#OFF"));
    _attributes.insert(std::make_pair("FFMUX", "#OFF"));
    _attributes.insert(std::make_pair("FFSR", "#OFF"));
    _attributes.insert(std::make_pair("OUTMUX", "#OFF"));
    _attributes.insert(std::make_pair("USED", "#OFF"));
}

/*!
 *
 * @return Name of this QuarterSlicel.
 */
const std::string &QuarterSlicel::get_name() const {
    return _name;
}

/*!
 *
 * @param name New name of the QuarterSlicel.
 */
void QuarterSlicel::set_name(const std::string &name) {
    QuarterSlicel::_name = name;
}

/*!
 * Sets the value of an attribute or adds it if it doesn't exist yet.
 *
 * @param attr Name of the attribute.
 * @param val New attribute value.
 */
void QuarterSlicel::set_attribute(const std::string attr, const std::string val) {
    if(_attributes.find(attr) != _attributes.end()) {
        _attributes[attr] = val;
    }
    else {
        _attributes.insert(std::make_pair(attr, val));
    }
}

/*!
 * Returns the value of the requestet attribute or an empty string if the attribute doesn't exist.
 *
 * @param attr Name of the attribute.
 * @return Value of the attribute.
 */
const std::string QuarterSlicel::get_attribute(std::string &attr) const {
    if(_attributes.find(attr) != _attributes.end()) {
        return _attributes.at(attr);
    }
    else {
        return "";
    }
}

std::ostream &operator<<(std::ostream &os, QuarterSlicel const &rhs) {
    os << rhs._name << "5FFINIT::" <<  rhs._attributes.at("5FFINIT") << " "
       << rhs._name << "5FFMUX::" << rhs._attributes.at("5FFMUX") << " "
       << rhs._name << "5FFSR::" << rhs._attributes.at("5FFSR") << std::endl << "       ";

    if(rhs._attributes.at("5LUT") == "#OFF") {
        os << rhs._name << "5LUT::#OFF" << std::endl << "       ";
    }
    else {
        os << rhs._name << "5LUT:" << rhs._attributes.at("5LUTNAME") << ":#LUT:O5=" << rhs._attributes.at("5LUT")
           << std::endl << "       ";
    }

    if(rhs._attributes.at("6LUT") == "#OFF") {
        os << rhs._name << "6LUT::#OFF" << std::endl << "       ";
    }
    else {
        os << rhs._name << "6LUT:" << rhs._attributes.at("6LUTNAME") << ":#LUT:O6=" << rhs._attributes.at("6LUT")
           << std::endl << "       ";
    }


    os << rhs._name << "CY0::" << rhs._attributes.at("CY0") << " "
       << rhs._name << "FF:" << rhs._attributes.at("FFNAME") << ":" << rhs._attributes.at("FF") << " "
       << rhs._name << "FFINIT::" << rhs._attributes.at("FFINIT") << " "
       << rhs._name << "FFMUX::" << rhs._attributes.at("FFMUX") << " "
       << rhs._name << "FFSR::" << rhs._attributes.at("FFSR") << " "
       << rhs._name << "OUTMUX::" << rhs._attributes.at("OUTMUX") << " "
       << rhs._name << "USED::" << rhs._attributes.at("USED") << std::endl << "       ";

    return os;
}
