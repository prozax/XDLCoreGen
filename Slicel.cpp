#include "Slicel.h"

/*!
 * Creates an unplaced Slicel instance with four QuarterSlicel instances called A, B, C and D.
 *
 * @param name Name of the slice.
 */
Slicel::Slicel(const std::string &name): Slice(name), _a("A"), _b("B"), _c("C"), _d("D"){
    _attributes.insert(std::make_pair("PRECYINIT", "#OFF"));
    _attributes.insert(std::make_pair("SRUSEDMUX", "#OFF"));
    _attributes.insert(std::make_pair("SYNC_ATTR", "#OFF"));
    _attributes.insert(std::make_pair("COUTUSED", "#OFF"));
    _attributes.insert(std::make_pair("CLKINV", "#OFF"));
}

std::ostream &operator<<(std::ostream &os, Slicel const &rhs) {
    os << "inst \"" << rhs._name << R"(" "SLICEL", )";

    if(rhs.is_placed())
        os << "placed " << rhs._primitive_site->get_parent()->get_name() << " "
           << rhs._primitive_site->get_name() << "," << std::endl;
    else
        os << "unplaced ," << std::endl;

    os << "  cfg \" ";
    os << rhs._a;
    os << rhs._b;
    os << rhs._c;
    os << rhs._d;
    os << "PRECYINIT::" << rhs._attributes.at("PRECYINIT") << " ";
    os << "SRUSEDMUX::" << rhs._attributes.at("SRUSEDMUX") << " ";
    os << "COUTUSED::" << rhs._attributes.at("COUTUSED") << " ";
    os << "CLKINV::" << rhs._attributes.at("CLKINV") << " ";
    os << "SYNC_ATTR::" << rhs._attributes.at("SYNC_ATTR") << " \"" << std::endl << ";";

    return os;
}

/*!
 * Sets an attribute in the slicel. If the attribute is not found in the slicel it will be set in the
 * QuarterSlicel according to the first letter of the attribute name. If the first letter doesn't
 * correspond to a QuarterSlicel or doesn't exist in the QuarterSlicel it will be ignored.
 *
 * @param attr Name of the attribute.
 * @param val New value of the attribute.
 */
void Slicel::set_attribute(std::string attr, std::string val) {
    if(_attributes.find(attr) != _attributes.end()) {
        _attributes[attr] = val;
    }
    else {
        switch (attr.at(0)) {
            case 'A':
                _a.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'B':
                _b.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'C':
                _c.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            case 'D':
                _d.set_attribute(attr.substr(1, std::string::npos), val);
                break;
            default:
                break;
        }
    }
}

/*!
 *
 * @param attr Name of a attribute in the Slicel or in a QuarterSlicel.
 * @return Value of the attribute or an empty string if the attribute doesn't exist.
 */
const std::string Slicel::get_attribute(std::string attr) const {
    std::string ret = "";

    if(_attributes.find(attr) != _attributes.end()) {
        return _attributes.at(attr);
    }
    else {
        switch (attr.at(0)) {
            case 'A':
                ret = _a.get_attribute(attr);
                break;
            case 'B':
                ret = _b.get_attribute(attr);
                break;
            case 'C':
                ret = _c.get_attribute(attr);
                break;
            case 'D':
                ret = _d.get_attribute(attr);
                break;
            default:
                break;
        }
    }

    return ret;
}



