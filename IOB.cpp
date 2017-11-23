
#include "IOB.h"

IOB::IOB(const std::string &_name) : _name(_name), _placed(false) {
    _attributes.insert(std::make_pair("DELAY_SELECT", "#OFF"));
    _attributes.insert(std::make_pair("DIFFI_INUSED", "#OFF"));
    _attributes.insert(std::make_pair("DIFF_TERM", "#OFF"));
    _attributes.insert(std::make_pair("DISABLE_GTS", "#OFF"));
    _attributes.insert(std::make_pair("IBUF_LOW_PWR", "#OFF"));
    _attributes.insert(std::make_pair("IUSED", "#OFF"));
    _attributes.insert(std::make_pair("OUSED", "#OFF"));
    _attributes.insert(std::make_pair("PADOUTUSED", "#OFF"));
    _attributes.insert(std::make_pair("PULLTYPE", "#OFF"));
    _attributes.insert(std::make_pair("TUSED", "#OFF"));
    _attributes.insert(std::make_pair("OUTBUF", ""));
    _attributes.insert(std::make_pair("PAD", "#OFF"));
    _attributes.insert(std::make_pair("DRIVE", "12"));
    _attributes.insert(std::make_pair("OSTANDARD", "LVCMOS25"));
    _attributes.insert(std::make_pair("ISTANDARD", "LVCMOS25"));
    _attributes.insert(std::make_pair("SLEW", "SLOW"));
}


std::ostream &operator<<(std::ostream &os, IOB const &rhs) {
    os << "inst \"" << rhs._name << R"(" "IOB", )";

    if(rhs.is_placed()) {
        os << "placed " << rhs._primitive_site->get_parent() << " "
           << rhs._primitive_site->get_name() << "," << std::endl;
    }
    else {
        os << "unplaced ," << std::endl;
    }

    os << "  cfg \" ";

    int linebreak = 0;
    for(auto a: rhs._attributes){
        if(a.first == "PAD" && a.second != "#OFF"
           || a.first == "OUTBUF"
           || a.first == "INBUF") {

            if(!a.second.empty())
                os << a.first << ":" << a.second << ": ";
        }
        else {
            os << a.first << "::" << a.second << " ";
        }

        linebreak++;

        if(linebreak % 4 == 0) {
            os << std::endl << "    ";
        }
    }

    os << " \"" << std::endl << ";";

    return os;
}

bool IOB::is_placed()const {
    return _placed;
}

void IOB::set_attribute(std::string attr, std::string val) {
    if(_attributes.find(attr) != _attributes.end()) {
        _attributes[attr] = val;
    }
    else {
        _attributes.insert(std::make_pair(attr, val));
    }
}
