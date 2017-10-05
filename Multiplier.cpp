
#include "Multiplier.h"
#include "Device.h"

int Multiplier::_multiplier_count = 0;

Multiplier::Multiplier(int a_size, int b_size) {
    _name = "Multiplier<" + std::to_string(_multiplier_count) + ">";
    _row_count = a_size/2 + 1;


    // creating connections between slices
    for(int i = 0; i < _row_count; i++) {
        create_row(a_size, b_size, i);

        if(i > 0) {
            for(int j = 0; j < (b_size/4)+1; j++) {
                std::string current_name = _name + "Slicel<" + std::to_string(i) + "_" + std::to_string(j) + ">";
                std::string previous_name = _name + "Slicel<" + std::to_string(i-1) + "_" + std::to_string(j) + ">";

                if(j > 0) {
                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 - 3) + ">")
                            ->set_outpin(previous_name, "AMUX")
                            ->add_inpin(_name + "Slicel<" + std::to_string(i) + "_" + std::to_string(j-1) + ">", "C1");

//                    if(j != (b_size/4)) {
                        add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 - 2) + ">")
                                ->set_outpin(previous_name, "BMUX")
                                ->add_inpin(_name + "Slicel<" + std::to_string(i) + "_" + std::to_string(j-1) + ">", "D1");
//                    }

                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 - 1) + ">")
                            ->set_outpin(previous_name, "CMUX")
                            ->add_inpin(current_name, "A1");
                }

                add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j*4) + ">")
                        ->set_outpin(previous_name, "DMUX")
                        ->add_inpin(current_name, "B1");

                if(j == (b_size/4)) {
                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 + 1) + ">")
                            // DMUX instead of COUT
                            ->set_outpin("carry_route" + std::to_string(i-1), "AMUX")
                            ->add_inpin(current_name,  "C1");
                }
            }
        }
    }


    // adding ports for inputs
    add_input_ports();


    _inst_name = _slices.front().get_name();
    _multiplier_count++;

//    add_port("Multiplier_Slicel<" + std::to_string(slice_count-1) + ">co", _slices.back(), "COUT");
}

void Multiplier::create_row(int a_size, int b_size, int row) {
    // LUT inputs: A1: t - A2: an - A3: an-1 - A4: bm-1 - A5: bm - A6: bm+1

    int slice_count = (b_size/4)+1;

    for(int i = 0; i < slice_count; i++) {
        std::string slice_name = _name + "Slicel<" + std::to_string(row) + "_" + std::to_string(i) + ">";
        _slices.push_back(Slicel(slice_name));
        Slicel &current_slice = _slices.back();

        // connecting a inputs

        int an = i * 4; // a input index at B LUT

        if(an-2 >= 0 && an-2 < a_size) {
            add_interconnect("input_a" + std::to_string(an-2))->add_inpin(slice_name, "A3");
        }
        if(an-1 >= 0 && an-1 < a_size) {
            add_interconnect("input_a" + std::to_string(an-1))->add_inpin(slice_name, "A2");
            add_interconnect("input_a" + std::to_string(an-1))->add_inpin(slice_name, "B3");
        }
        if(an >= 0 && an < a_size) {
            add_interconnect("input_a" + std::to_string(an))->add_inpin(slice_name, "B2");
            add_interconnect("input_a" + std::to_string(an))->add_inpin(slice_name, "C3");
        }
        if(an+1 >= 0 && an+1 < a_size) {
            add_interconnect("input_a" + std::to_string(an+1))->add_inpin(slice_name, "C2");
            add_interconnect("input_a" + std::to_string(an+1))->add_inpin(slice_name, "D3");
        }
        if(an+2 >= 0 && an+2 < a_size) {
            add_interconnect("input_a" + std::to_string(an+2))->add_inpin(slice_name, "D2");
        }



        // connecting b inputs
        int bm = row * 2;

        if(bm-1 >= 0) {
            add_interconnect("input_b" + std::to_string(bm-1))->add_inpin(slice_name, "A4");
            add_interconnect("input_b" + std::to_string(bm-1))->add_inpin(slice_name, "B4");
            add_interconnect("input_b" + std::to_string(bm-1))->add_inpin(slice_name, "C4");
            add_interconnect("input_b" + std::to_string(bm-1))->add_inpin(slice_name, "D4");
        }

        if(bm >= 0 && bm < b_size) {
            add_interconnect("input_b" + std::to_string(bm))->add_inpin(slice_name, "A5");
            add_interconnect("input_b" + std::to_string(bm))->add_inpin(slice_name, "B5");
            add_interconnect("input_b" + std::to_string(bm))->add_inpin(slice_name, "C5");
            add_interconnect("input_b" + std::to_string(bm))->add_inpin(slice_name, "D5");
        }

        if(bm+1 >= 0 && bm+1 < b_size) {
            add_interconnect("input_b" + std::to_string(bm+1))->add_inpin(slice_name, "A6");
            add_interconnect("input_b" + std::to_string(bm+1))->add_inpin(slice_name, "B6");
            add_interconnect("input_b" + std::to_string(bm+1))->add_inpin(slice_name, "C6");
            add_interconnect("input_b" + std::to_string(bm+1))->add_inpin(slice_name, "D6");
        }


        if(row == 0) {
            // bm-1
            add_ground_connection(slice_name, "A4");
            add_ground_connection(slice_name, "B4");
            add_ground_connection(slice_name, "C4");
            add_ground_connection(slice_name, "D4");

            // t inputs of the first row
            add_ground_connection(slice_name, "A1");
            add_ground_connection(slice_name, "B1");

            if(i == slice_count-1) {
                add_vcc_connection(slice_name, "C1");
            } else {
                add_ground_connection(slice_name, "C1");
                add_ground_connection(slice_name, "D1");
            }
        }

        if(row == _row_count-1) {
            // bm, bm+1
            add_ground_connection(slice_name, "A5");
            add_ground_connection(slice_name, "B5");
            add_ground_connection(slice_name, "C5");
            add_ground_connection(slice_name, "D5");
            add_ground_connection(slice_name, "A6");
            add_ground_connection(slice_name, "B6");
            add_ground_connection(slice_name, "C6");
            add_ground_connection(slice_name, "D6");
        }

        if(i == slice_count-1) {
            add_ground_connection(slice_name, "B2");
            add_ground_connection(slice_name, "C2");
            add_ground_connection(slice_name, "C3");
            add_ground_connection(slice_name, "D2");
            add_ground_connection(slice_name, "D3");
            add_vcc_connection(slice_name, "D1");
        }


        if(i == 0) {
            current_slice.set_attribute("PRECYINIT", "1");

            add_ground_connection(slice_name, "A1");
            add_ground_connection(slice_name, "A2");
            add_ground_connection(slice_name, "A3");
            add_ground_connection(slice_name, "B3");

            add_interconnect("input_p" + std::to_string(row*2))->set_outpin(slice_name, "BMUX");
            add_interconnect("input_p" + std::to_string(row*2 + 1))->set_outpin(slice_name, "CMUX");

            if(row == _row_count-1) {
                add_interconnect("input_p" + std::to_string(row*2 + 2))->set_outpin(slice_name, "DMUX");
            }
        }
        else {
            add_interconnect(_name + "carry<" + std::to_string(row) + "_" + std::to_string(i-1) + "to" +  std::to_string(i) + ">")
                    ->set_outpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string(i-1) + ">", "COUT")
                    ->add_inpin(slice_name, "CIN");

            if(row == _row_count-1) {
                add_interconnect("input_p" + std::to_string(row*2 + i*4 - 1))->set_outpin(slice_name, "AMUX");
                add_interconnect("input_p" + std::to_string(row*2 + i*4))->set_outpin(slice_name, "BMUX");
                add_interconnect("input_p" + std::to_string(row*2 + i*4 + 1))->set_outpin(slice_name, "CMUX");
                add_interconnect("input_p" + std::to_string(row*2 + i*4 + 2))->set_outpin(slice_name, "DMUX");


                if(i == (b_size/4)) {
//                    Slicel &cr_slice = create_carry_route_slice(row);
//                    add_interconnect("carry_routing_slice_" + std::to_string(row))
//                            ->set_outpin(slice_name, "COUT")
//                            ->add_inpin(cr_slice.get_name(), "CIN");

                    add_interconnect("input_p" + std::to_string(row*2 + i*4 + 3))
                            ->set_outpin("carry_route" + std::to_string(row), "AMUX");
                }
            }
        }

        current_slice.set_attribute("AUSED", "#OFF");
        current_slice.set_attribute("BUSED", "#OFF");
        current_slice.set_attribute("CUSED", "#OFF");
        current_slice.set_attribute("DUSED", "#OFF");
        current_slice.set_attribute("COUTUSED", "0");

//        _slices.back().set_attribute("ACY0", "O5");
//        _slices.back().set_attribute("BXY0", "O5");
//        _slices.back().set_attribute("CCY0", "O5");
//        _slices.back().set_attribute("DCY0", "O5");

        current_slice.set_attribute("AOUTMUX", "XOR");
        current_slice.set_attribute("BOUTMUX", "XOR");
        current_slice.set_attribute("COUTMUX", "XOR");
        current_slice.set_attribute("DOUTMUX", "XOR");

        // booth en/dec
        std::string a_lut = "((~A1*((~A2*(((~A3*A5)+(A3*(~A4*A5)))@A6))+(A2*((~A3*(A4@(A5@A6)))+(A3*(((~A4*A5)+A4)@~A6))))))+(A1*((~A2*((~A3*((A4*A5)@A6))+(A3*(A4@(A5@A6)))))+(A2*(((~A3*(~A4+(A4*A5)))+(A3*A5))@~A6)))))";
        // not(compl) add configuration
        std::string b_lut = "(((~A3*A5)+(A3*(~A4*A5)))@~A6)*(A2+~A2)*(A1+~A1)";
        // simple adder
        std::string c_lut = "A6*(A5+~A5)*(A4+~A4)*(A3+~A3)*(A2+~A2)*(A1+~A1)";

        current_slice.set_attribute("A6LUT", a_lut);
        current_slice.set_attribute("A6LUTNAME", slice_name + "A6");

        current_slice.set_attribute("B6LUT", a_lut);
        current_slice.set_attribute("B6LUTNAME", slice_name + "B6");

        current_slice.set_attribute("C6LUT", a_lut);
        current_slice.set_attribute("C6LUTNAME", slice_name + "C6");

        current_slice.set_attribute("D6LUT", a_lut);
        current_slice.set_attribute("D6LUTNAME", slice_name + "D6");

        if(i == (b_size/4)) {
            current_slice.set_attribute("C6LUT", b_lut);
            current_slice.set_attribute("D6LUT", c_lut);
        }
    }
    std::string last_slice_name = _slices.back().get_name();

    Slicel &cr_slice = create_carry_route_slice(row);
    add_interconnect("carry_routing_slice_" + std::to_string(row))
            ->set_outpin(last_slice_name, "COUT")
            ->add_inpin(cr_slice.get_name(), "CIN");
}

void Multiplier::add_input_ports() {
    for (auto n: _net) {
        if(n.second.get_name().find("input_") != std::string::npos) {
            if(!n.second.get_outpin().empty()) {
                add_port(n.second.get_name().substr(6, std::string::npos),
                         n.second.get_outpin().get_instance(),
                         n.second.get_outpin().get_pin());
            }
            else {
                if(!n.second.get_inpins().empty()) {
                    n.second.get_inpins().at(0);
                    add_port(n.second.get_name().substr(6, std::string::npos),
                             n.second.get_inpins().at(0).get_instance(),
                             n.second.get_inpins().at(0).get_pin());
                }
            }
        }
    }
}

Slicel &Multiplier::create_carry_route_slice(int row) {
    _slices.push_back(Slicel("carry_route" + std::to_string(row)));
    _slices.back().set_attribute("AOUTMUX", "XOR");
    _slices.back().set_attribute("A6LUT", "A1");
    add_ground_connection(_slices.back().get_name(), "A1");
    return _slices.back();
}

void Multiplier::place(int x_pos, int y_pos, Device &device) {
    // the multiplier is rotated 90 degrees to fit the carry chain, so rows and columns are swapped
    for(int x = 0; x < _row_count; ++x) {
        for (int y = 0; y < _slices.size()/_row_count; ++y) {
            int pos = x * (_slices.size()/_row_count) + y;
            _slices.at(pos).set_primitive_site(device.get_slice(x + x_pos, y + y_pos));
            _slices.at(pos).set_placed(true);
        }
    }
}

