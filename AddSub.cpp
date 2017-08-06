#include "AddSub.h"

AddSub::AddSub(int bit_count) {

    int slice_count = (int)ceil((float)bit_count / 4.0f);
    int bits_remaining = bit_count;

    _name = "AddSub_Module<1>";
    _inst_name = "AddSub_Slicel<" + std::to_string(slice_count-1) + ">";

    for(int i = 0; i < slice_count; i++) {

        _slices.push_back(Slicel("AddSub_Slicel<" + std::to_string(i) + ">"));

        if(i == 0) {
            _slices.back().set_attribute("PRECYINIT", "0");
            add_port("AddSub_Slicel<" + std::to_string(i) + ">ci", _slices.back(), "CIN");
        }
        else {
            add_interconnect("AddSub_Slicel<" + std::to_string(i-1) + ">")
                    ->set_outpin(_slices.back().get_name(), "COUT")
                    ->add_inpin("AddSub_Slicel<" + std::to_string(i-1) + ">", "CIN");
        }

        add_port(_slices.back().get_name() + "a", _slices.back(), "A");
        add_port(_slices.back().get_name() + "b", _slices.back(), "B");
        add_port(_slices.back().get_name() + "c", _slices.back(), "C");
        add_port(_slices.back().get_name() + "d", _slices.back(), "D");
        add_port(_slices.back().get_name() + "i1", _slices.back(), "A5");
        add_port(_slices.back().get_name() + "i2", _slices.back(), "A6");


        _slices.back().set_attribute("AUSED", "0");
        _slices.back().set_attribute("BUSED", "0");
        _slices.back().set_attribute("CUSED", "0");
        _slices.back().set_attribute("DUSED", "0");

        _slices.back().set_attribute("ACY0", "O5");
        _slices.back().set_attribute("BXY0", "O5");
        _slices.back().set_attribute("CCY0", "O5");
        _slices.back().set_attribute("DCY0", "O5");

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

        //tmp.set_attribute("", "");
    }

    add_port("AddSub_Slicel<" + std::to_string(slice_count-1) + ">co", _slices.back(), "COUT");
}
