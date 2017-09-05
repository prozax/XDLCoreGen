
#include "Multiplier.h"
#include "Device.h"

int Multiplier::_multiplier_count = 0;

Multiplier::Multiplier(int a_size, int b_size) {
    _name = "Multiplier<" + std::to_string(_multiplier_count) + ">_HARD_MACRO";
    _row_count = a_size/2 + 1;


    // creating pins
//    for(int i = 0; i < a_size; i++) {
//        _pins.insert(std::make_pair("a" + std::to_string(i), IOB("a" + std::to_string(i))));
//        _pins.at("a" + std::to_string(i)).set_attribute("IUSED", "0");
//        _pins.at("a" + std::to_string(i)).set_attribute("INBUF", "input_a" + std::to_string(i));
//        _pins.at("a" + std::to_string(i)).set_attribute("IBUF_LOW_PWR", "TRUE");
//        _pins.at("a" + std::to_string(i)).set_attribute("PAD", "a" + std::to_string(i));
//
//        add_interconnect("input_a" + std::to_string(i))->set_outpin("a" + std::to_string(i), "I");
//    }
//
//    for(int i = 0; i < b_size; i++) {
//        _pins.insert(std::make_pair("b" + std::to_string(i), IOB("b" + std::to_string(i))));
//        _pins.at("b" + std::to_string(i)).set_attribute("IUSED", "0");
//        _pins.at("b" + std::to_string(i)).set_attribute("INBUF", "input_b" + std::to_string(i));
//        _pins.at("b" + std::to_string(i)).set_attribute("IBUF_LOW_PWR", "TRUE");
//        _pins.at("b" + std::to_string(i)).set_attribute("PAD", "b" + std::to_string(i));
//
//        add_interconnect("input_b" + std::to_string(i))->set_outpin("b" + std::to_string(i), "I");
//    }
//
//    for(int i = 0; i < (b_size + a_size + 4); i++) {
//        _pins.insert(std::make_pair("p" + std::to_string(i), IOB("p" + std::to_string(i))));
//        _pins.at("p" + std::to_string(i)).set_attribute("OUSED", "0");
//        _pins.at("p" + std::to_string(i)).set_attribute("OUTBUF", "output_p" + std::to_string(i));
//        _pins.at("p" + std::to_string(i)).set_attribute("PAD", "p" + std::to_string(i));
//        add_interconnect("output_p" + std::to_string(i))->add_inpin("p" + std::to_string(i), "O");
//    }




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
                            ->set_outpin(previous_name, "COUT")
                            ->add_inpin(current_name,  "C1");
                }
            }
        }
    }


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
            _slices.back().set_attribute("PRECYINIT", "1");

            add_ground_connection(slice_name, "A1");
            add_ground_connection(slice_name, "A2");
            add_ground_connection(slice_name, "A3");
            add_ground_connection(slice_name, "B3");

            add_port("p" + std::to_string(row*2), _slices.back(), "BMUX");
            add_port("p" + std::to_string(row*2 + 1), _slices.back(), "CMUX");
//            add_interconnect("output_p" + std::to_string(row*2))->set_outpin(slice_name, "BMUX");
//            add_interconnect("output_p" + std::to_string(row*2 + 1))->set_outpin(slice_name, "CMUX");

            if(row == _row_count-1) {
                add_port("p" + std::to_string(row*2 + 2), _slices.back(), "DMUX");
//                add_interconnect("output_p" + std::to_string(row*2 + 2))->set_outpin(slice_name, "DMUX");
            }
        }
        else {
            add_interconnect(_name + "carry<" + std::to_string(row) + "_" + std::to_string(i-1) + "to" +  std::to_string(i) + ">")
                    ->set_outpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string(i-1) + ">", "COUT")
                    ->add_inpin(slice_name, "CIN");

            if(row == _row_count-1) {
                add_port("p" + std::to_string(row*2 + i*4 - 1), _slices.back(), "AMUX");
                add_port("p" + std::to_string(row*2 + i*4), _slices.back(), "BMUX");
                add_port("p" + std::to_string(row*2 + i*4 + 1), _slices.back(), "CMUX");
                add_port("p" + std::to_string(row*2 + i*4 + 2), _slices.back(), "DMUX");

//                add_interconnect("output_p" + std::to_string(row*2 + i*4 - 1))->set_outpin(slice_name, "AMUX");
//                add_interconnect("output_p" + std::to_string(row*2 + i*4))->set_outpin(slice_name, "BMUX");
//                add_interconnect("output_p" + std::to_string(row*2 + i*4 + 1))->set_outpin(slice_name, "CMUX");
//                add_interconnect("output_p" + std::to_string(row*2 + i*4 + 2))->set_outpin(slice_name, "DMUX");


                if(i == (b_size/4)) {
                    add_port("p" + std::to_string(row*2 + i*4 + 3), _slices.back(), "COUT");
//                    add_interconnect("output_p" + std::to_string(row*2 + i*4 + 3))->set_outpin(slice_name, "COUT");
                }
            }
        }



        _slices.back().set_attribute("AUSED", "#OFF");
        _slices.back().set_attribute("BUSED", "#OFF");
        _slices.back().set_attribute("CUSED", "#OFF");
        _slices.back().set_attribute("DUSED", "#OFF");
        _slices.back().set_attribute("COUTUSED", "0");

//        _slices.back().set_attribute("ACY0", "O5");
//        _slices.back().set_attribute("BXY0", "O5");
//        _slices.back().set_attribute("CCY0", "O5");
//        _slices.back().set_attribute("DCY0", "O5");

        _slices.back().set_attribute("AOUTMUX", "XOR");
        _slices.back().set_attribute("BOUTMUX", "XOR");
        _slices.back().set_attribute("COUTMUX", "XOR");
        _slices.back().set_attribute("DOUTMUX", "XOR");

//        _slices.back().set_attribute("A5LUT", "A5");
//        _slices.back().set_attribute("A5LUTNAME", slice_name + "A5");
        _slices.back().set_attribute("A6LUT", "A1+A2+A3+A4+A5+A6");
        _slices.back().set_attribute("A6LUTNAME", slice_name + "A6");

//        _slices.back().set_attribute("B5LUT", "A5");
//        _slices.back().set_attribute("B5LUTNAME", slice_name + "B5");
        _slices.back().set_attribute("B6LUT", "A1+A2+A3+A4+A5+A6");
        _slices.back().set_attribute("B6LUTNAME", slice_name + "B6");

//        _slices.back().set_attribute("C5LUT", "A5");
//        _slices.back().set_attribute("C5LUTNAME", slice_name + "C5");
        _slices.back().set_attribute("C6LUT", "A1+A2+A3+A4+A5+A6");
        _slices.back().set_attribute("C6LUTNAME", slice_name + "C6");

//        _slices.back().set_attribute("D5LUT", "A5");
//        _slices.back().set_attribute("D5LUTNAME", slice_name + "D5");
        _slices.back().set_attribute("D6LUT", "A1+A2+A3+A4+A5+A6");
        _slices.back().set_attribute("D6LUTNAME", slice_name + "D6");
    }
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

