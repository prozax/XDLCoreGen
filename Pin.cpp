
#include "Pin.h"

Pin::Pin(std::string instance, std::string pin) : _instance(instance), _pin(pin) {

}

const std::string &Pin::get_instance() const {
    return _instance;
}

const std::string &Pin::get_pin() const {
    return _pin;
}

const bool Pin::empty() const {
    return _instance.empty() || _pin.empty();
}
