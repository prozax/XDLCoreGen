
#include "Pin.h"

/*!
 * @brief Constructor with instance name and pin name.
 *
 * @param instance Name of the PrimitiveSite instance that this pin belongs to.
 * @param pin Name of the pin.
 */
Pin::Pin(std::string instance, std::string pin) : _instance(instance), _pin(pin) {}

/*!
 * @brief Instance name getter.
 *
 * @returns Name of the PrimitiveSite this pin belongs to.
 */
const std::string &Pin::get_instance() const {
    return _instance;
}

/*!
 * @brief Pin name getter.
 *
 * @returns Name of the pin.
 */
const std::string &Pin::get_pin() const {
    return _pin;
}

/*!
 * @brief Checks whether this pin has the instance name and pin name set.
 *
 * @returns True if instance name or pin name are empty, false if at least one is set.
 */
const bool Pin::empty() const {
    return _instance.empty() || _pin.empty();
}
