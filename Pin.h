
#ifndef XDLCOREGEN_PIN_H
#define XDLCOREGEN_PIN_H

#include <string>

class Pin {
private:
    std::string _instance;
    std::string _pin;

public:
    Pin(std::string, std::string);

    const std::string &get_instance() const;
    const std::string &get_pin() const;
    const bool empty() const;
};


#endif //XDLCOREGEN_PIN_H
