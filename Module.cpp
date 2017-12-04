#include "Module.h"

/*!
 * Constructor for a Module with no name ("_HARD_MACRO" is always added).
 *
 */
Module::Module(): Module("") {}

/*!
 * Constructor for a Module with a name.
 *
 * @param name Name of the module.
 */
Module::Module(std::string name): _name(name) {}

std::ostream &operator<<(std::ostream &os, Module const &rhs) {
    os << "module \"" << rhs._name << "_HARD_MACRO" << "\" \"" << rhs._inst_name << R"(", cfg "_SYSTEM_MACRO::FALSE")"
                                                                                 << std::endl << ";" << std::endl;

    for(auto i: rhs._ports) {
        os << i << std::endl;
    }

    os << std::endl;

    for (auto p: rhs._pins) {
        os << p.second << std::endl;
    }

    os << std::endl;

    for (auto i: rhs._slices) {
        os << i << std::endl;
    }

    os << std::endl;

    for (auto i: rhs._net) {
        os << i.second << std::endl;
    }

    os << "endmodule \"" << rhs._name<< "_HARD_MACRO" << "\";" << std::endl;

    os << std::endl;
    os << "# =======================================================" << std::endl;
    os << "# SUMMARY" << std::endl;
    os << "# Number of Slices: " << std::to_string(rhs._slices.size()) << std::endl;
    os << "# Number of Ports: " << std::to_string(rhs._ports.size()) << std::endl;
    os << "# Number of Nets: " << std::to_string(rhs._net.size()) << std::endl;
    os << "# =======================================================";


    return os;
}

/*!
 * Creates a new net if it doesn't exist yet and returns a pointer to it.
 *
 * @param name Name of the Net.
 */
Net* Module::add_interconnect(const std::string name) {
    if(_net.count(name) == 0) {
        _net.emplace(name, Net(name));
    }

    return &(_net.at(name));
}

/*!
 * Adds a pin to the ground (LOGIC 0) net and creates a port for gnd.
 *
 * @param instance_name Name of the primitive instance.
 * @param pin_name Name of the pin to connect.
 */
void Module::add_ground_connection(std::string instance_name, std::string pin_name) {
    if(_net.count("PORT_LOGIC0_" + _name) == 0) {
        // creating port and net for gnd
        add_port("gnd", instance_name, pin_name);
        _net.emplace("PORT_LOGIC0_" + _name, Net("PORT_LOGIC0_" + _name, "gnd"));
    }

    _net.at("PORT_LOGIC0_" + _name).add_inpin(instance_name, pin_name);
}

/*!
 * Adds a pin to the vcc (LOGIC 1) net and creates a port for vcc.
 *
 * @param instance_name Name of the primitive instance.
 * @param pin_name Name of the pin to connect.
 */
void Module::add_vcc_connection(std::string instance_name, std::string pin_name) {
    if(_net.count("PORT_LOGIC1_" + _name) == 0) {
        // creating port and net for vcc
        add_port("vcc", instance_name, pin_name);
        _net.emplace(std::make_pair("PORT_LOGIC1_" + _name, Net("PORT_LOGIC1_" + _name, "vcc"));
    }

    _net.at("PORT_LOGIC1_" + _name).add_inpin(instance_name, pin_name);
}

/*!
 * Adds a new port to the module.
 *
 * @param portname Name of the port.
 * @param slice Name of the slice.
 * @param slice_pin Name of the pin on the slice.
 */
void Module::add_port(std::string portname, std::string slice, std::string slice_pin) {
    _ports.emplace_back(portname, slice, slice_pin);
}

/*!
 * Adds a new port to the module.
 *
 * @param portname Name of the port.
 * @param slice Reference to a Slice.
 * @param slice_pin Name of the pin on the slice.
 */
void Module::add_port(std::string portname, Slice & slice, std::string slice_pin) {
    add_port(portname, slice.get_name(), slice_pin);
}

/*!
 * Returns a reference to the deque containing all slices in thie module.
 *
 * @returns Reference to the deque containing the module slices.
 */
std::deque<Slicel> &Module::get_slices() {
    return _slices;
}

/*!
 * Places slices from the model. The placing algorithm tries to keep the placement in a
 * square while keeping carry chains intact by continuing a column as long as carry outputs are used.
 *
 * @param x_offset X offset from the device origin.
 * @param y_offset Y offset from the device origin.
 * @param device Device reference to retrieve empty slices.
 */
void Module::place(int x_offset, int y_offset, Device &device) {
    int row = 0;
    int column = 0;
    auto max_column = (int)std::ceil(std::sqrt(_slices.size()));

    for(size_t pos = 0; pos < _slices.size(); ++pos) {
        while (_slices.at(pos).get_primitive_site() == nullptr) {
            _slices.at(pos).set_primitive_site(device.get_slice(row + y_offset, column + x_offset));
            _slices.at(pos).set_placed(true);

            // if COUT is used this slice is probably part of a carry chain and the row has to be continued
            if (column >= device.get_row_count()
                || (column >= max_column && _slices.at(pos).get_attribute("COUTUSED").compare("#OFF") == 0)) {
                column = 0;
                ++row;
            } else {
                ++column;
            }

            // throw error if there are no slice primitves left
            if(_slices.at(pos).get_primitive_site() == nullptr
               && column == device.get_row_count()
               && row == device.get_column_count()) {
                throw 1;
            }
        }
    }
}

/*!
 * Adds a Slicel to the module.
 *
 * @param s Slicel instance to be added to the module.
 */
void Module::add_slice(Slicel s) {
    _slices.push_back(s);
}


