
#include "Example.h"
#include "Device.h"
#include "Module.h"
#include "Design.h"

Example::Example() {
    Device d = Device("xc6vlx75tff484-3", "./devices/xc6vlx75tff484-3.xdl");

    //Multiplier test_multi = Multiplier(a_size, b_size, is_pipelined);
    Module m = Module("testmodule");
    Slicel s = Slicel("testslicel1");
    s.set_attribute("A6LUT", "A1*A2+A3");
    s.set_attribute("AOUTMUX", "O6");
    m.add_slice(s);

    s = Slicel("testslicel2");
    s.set_attribute("B5LUT", "A5");
    s.set_attribute("BOUTMUX", "O5");
    m.add_slice(s);

    m.add_interconnect("net1")->set_outpin("testslicel1", "AMUX")->add_inpin("testslicel2", "B5");
    m.add_vcc_connection("testslicel1", "A2");
    m.add_ground_connection("testslicel1", "A3");

    m.add_port("in(0)", "testslicel1", "A1");
    m.add_interconnect("inpin<0>")->add_inpin("testslicel1", "A1");

    m.add_port("out(0)", s, "BMUX");
    m.add_interconnect("outpin<0>")->set_outpin(s.get_name(), "BMUX");

    Design test_design = Design(d);
    test_design.add_module(m);
    test_design.place();
}
