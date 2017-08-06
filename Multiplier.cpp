
#include "Multiplier.h"

int Multiplier::_multiplier_count = 0;

Multiplier::Multiplier(int a_size, int b_size) {
    _name = "Multiplier<" + std::to_string(_multiplier_count) + ">";
    _row_count = a_size/2 + 1;


    for(int i = 0; i < _row_count; i++) {
        create_row(b_size, i);

        if(i > 0) {
            for(int j = 0; j < (b_size/4)+1; j++) {
                std::string current_name = _name + "Slicel<" + std::to_string(i) + "," + std::to_string(j) + ">";
                std::string previous_name = _name + "Slicel<" + std::to_string(i-1) + "," + std::to_string(j) + ">";

                add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j*4) + ">")
                        ->set_outpin(previous_name, "DMUX")
                        ->add_inpin(current_name, "B1");

                if(j < 0) {
                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 + 1) + ">")
                            ->set_outpin(previous_name, "AMUX")
                            ->add_inpin(current_name, "C1");

                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 + 2) + ">")
                            ->set_outpin(previous_name, "BMUX")
                            ->add_inpin(current_name, "D1");

                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 + 3) + ">")
                            ->set_outpin(previous_name, "CMUX")
                            ->add_inpin(current_name, "A1");
                }

                if(j == (b_size/4)) {
                    add_interconnect("t<" + std::to_string(i) + "," + std::to_string(j * 4 + 3) + ">")
                            ->set_outpin(previous_name, "COUT")
                            ->add_inpin(current_name,  "C1");
                }
            }
        }
    }


    _inst_name = _slices.front().get_name();

//    add_port("Multiplier_Slicel<" + std::to_string(slice_count-1) + ">co", _slices.back(), "COUT");
}

void Multiplier::create_row(int b_size, int row) {
    int slice_count = (b_size/4)+1;

    for(int i = 0; i < slice_count; i++) {
        _slices.push_back(Slicel(_name + ">Slicel<" + std::to_string(row) + "," + std::to_string(i) + ">"));


        if(row == 0) {
            // bm-1
            add_ground_connection(_slices.back().get_name(), "A4");
            add_ground_connection(_slices.back().get_name(), "B4");
            add_ground_connection(_slices.back().get_name(), "C4");
            add_ground_connection(_slices.back().get_name(), "D4");

            if(i == slice_count-1) {
                add_vcc_connection(_slices.back().get_name(), "C1");
            }
        }

        if(row == _row_count-1) {
            // bm, bm+1
            add_ground_connection(_slices.back().get_name(), "A5");
            add_ground_connection(_slices.back().get_name(), "B5");
            add_ground_connection(_slices.back().get_name(), "C5");
            add_ground_connection(_slices.back().get_name(), "D5");
            add_ground_connection(_slices.back().get_name(), "A6");
            add_ground_connection(_slices.back().get_name(), "B6");
            add_ground_connection(_slices.back().get_name(), "C6");
            add_ground_connection(_slices.back().get_name(), "D6");
        }

        if(i == slice_count-1) {
            add_ground_connection(_slices.back().get_name(), "B2");
            add_ground_connection(_slices.back().get_name(), "C2");
            add_ground_connection(_slices.back().get_name(), "C3");
            add_ground_connection(_slices.back().get_name(), "D2");
            add_ground_connection(_slices.back().get_name(), "D3");
            add_vcc_connection(_slices.back().get_name(), "D1");
        }


        if(i == 0) {
            _slices.back().set_attribute("PRECYINIT", "1");

            add_ground_connection(_slices.back().get_name(), "A1");
            add_ground_connection(_slices.back().get_name(), "A2");
            add_ground_connection(_slices.back().get_name(), "A3");
            add_ground_connection(_slices.back().get_name(), "B3");

            add_port("p" + std::to_string(row*2), _slices.back(), "BMUX");
            add_port("p" + std::to_string(row*2 + 1), _slices.back(), "CMUX");

            if(row == _row_count-1) {
                add_port("p" + std::to_string(row*2 + 2), _slices.back(), "DMUX");
            }
        }
        else {
            add_interconnect(_name + ">Slicel<" + std::to_string(row) + "," + std::to_string(i-1) + ">")
                    ->set_outpin(_slices.back().get_name(), "COUT")
                    ->add_inpin(_name + ">Slicel<" + std::to_string(row) + "," + std::to_string(i-1) + ">", "CIN");

            if(row == _row_count-1) {
                add_port("p" + std::to_string(row*2 + i*4 - 1), _slices.back(), "AMUX");
                add_port("p" + std::to_string(row*2 + i*4), _slices.back(), "BMUX");
                add_port("p" + std::to_string(row*2 + i*4 + 1), _slices.back(), "CMUX");
                add_port("p" + std::to_string(row*2 + i*4 + 2), _slices.back(), "DMUX");

                if(i == (b_size/4)) {
                    add_port("p" + std::to_string(row*2 + i*4 + 3), _slices.back(), "COUT");
                }
            }
        }



        _slices.back().set_attribute("AUSED", "0");
        _slices.back().set_attribute("BUSED", "0");
        _slices.back().set_attribute("CUSED", "0");
        _slices.back().set_attribute("DUSED", "0");

        _slices.back().set_attribute("ACY0", "O5");
        _slices.back().set_attribute("BXY0", "O6");
        _slices.back().set_attribute("CCY0", "O6");
        _slices.back().set_attribute("DCY0", "O6");

        _slices.back().set_attribute("AOUTMUX", "XOR");
        _slices.back().set_attribute("BOUTMUX", "XOR");
        _slices.back().set_attribute("COUTMUX", "XOR");
        _slices.back().set_attribute("DOUTMUX", "XOR");

        _slices.back().set_attribute("A5LUT", "A5");
        _slices.back().set_attribute("A5LUTNAME", _slices.back().get_name() + "A5");
        _slices.back().set_attribute("A6LUT", "A5@A4");
        _slices.back().set_attribute("A6LUTNAME", _slices.back().get_name() + "A6");

        _slices.back().set_attribute("B5LUT", "A5");
        _slices.back().set_attribute("B5LUTNAME", _slices.back().get_name() + "B5");
        _slices.back().set_attribute("B6LUT", "A5@A4");
        _slices.back().set_attribute("B6LUTNAME", _slices.back().get_name() + "B6");

        _slices.back().set_attribute("C5LUT", "A5");
        _slices.back().set_attribute("C5LUTNAME", _slices.back().get_name() + "C5");
        _slices.back().set_attribute("C6LUT", "A5@A4");
        _slices.back().set_attribute("C6LUTNAME", _slices.back().get_name() + "C6");

        _slices.back().set_attribute("D5LUT", "A5");
        _slices.back().set_attribute("D5LUTNAME", _slices.back().get_name() + "D5");
        _slices.back().set_attribute("D6LUT", "A5@A4");
        _slices.back().set_attribute("D6LUTNAME", _slices.back().get_name() + "D6");
    }
}

