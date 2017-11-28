
#include "ExampleModule.h"
#include "../Design.h"

ExampleModule::ExampleModule() {
    Device d = Device("./devices/xc6vlx75tff484-3.xdl");

    //Multiplier test_multi = Multiplier(a_size, b_size, is_pipelined);
    _name = "testmodule";
    Slicel s = Slicel("testslicel1");
    s.set_attribute("A6LUT", "A1*A2+A3");
    s.set_attribute("AOUTMUX", "O6");
    add_slice(s);

    s = Slicel("testslicel2");
    s.set_attribute("B5LUT", "A5");
    s.set_attribute("BOUTMUX", "O5");
    add_slice(s);

    add_interconnect("net1")->set_outpin("testslicel1", "AMUX")->add_inpin("testslicel2", "B5");
    add_vcc_connection("testslicel1", "A2");
    add_ground_connection("testslicel1", "A3");

    add_port("in(0)", "testslicel1", "A1");
    add_interconnect("inpin<0>")->add_inpin("testslicel1", "A1");

    add_port("out(0)", s, "BMUX");
    add_interconnect("outpin<0>")->set_outpin(s.get_name(), "BMUX");
}

void ExampleModule::place(int x_offset, int y_offset, Device &device) {
    for(size_t pos = 0; pos < _slices.size(); ++pos) {
        _slices.at(pos).set_primitive_site(device.get_slice(static_cast<int>(pos + y_offset), x_offset));
        _slices.at(pos).set_placed(true);
    }
}