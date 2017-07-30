
#include "Net.h"

Net* Net::set_outpin(std::string instance, std::string pin) {
    _outpin.clear();
    _outpin.insert(std::make_pair(instance, pin));
    return this;
}

Net* Net::add_inpin(std::string instance, std::string pin) {
    _inpins.insert(std::make_pair(instance, pin));
    return this;
}

const std::string Net::to_string() const {
    std::ostringstream ret;

    ret << "outpin \"";
    ret << _outpin.begin()->first << "\" \"" << _outpin.begin()->second << "\" ," << std::endl;

    for(auto const& i: _inpins) {
        ret << "inpin \"";
        ret << i.first << "\" \"" << i.second << "\" ," << std::endl;
    }

    return ret.str();
}

bool Net::empty() {
    return _outpin.empty() || _inpins.empty();
}
