
#include "Multiplier.h"
#include "Device.h"
#include <math.h>

int Multiplier::_multiplier_count = 0;

Multiplier::Multiplier(int a_size, int b_size, bool is_pipelined) : _a_size(a_size), _b_size(b_size), _is_pipelined(is_pipelined) {
    _name = "Multiplier<" + std::to_string(_multiplier_count) + ">";
    _row_count = a_size/2 + 1;

    int lut_count = a_size + 5;
    int ff_luts_a[_row_count];
    int ff_luts_b[_row_count];
    int ff_luts_p[_row_count];
    int ff_luts[_row_count];
    std::string outpin = _is_pipelined ? "Q" : "MUX";

    std::string letter[] = {"A", "B", "C", "D"};

    // creating connections between slices
    for(int row = 0; row < _row_count; row++) {
        ff_luts_a[row] = _is_pipelined && row<_row_count-1 ? a_size : 0;
        ff_luts_b[row] = _is_pipelined && row<_row_count-1 ? b_size - 1 - row * 2 : 0;
        ff_luts_p[row] = _is_pipelined ? row * 2 : 0;
        ff_luts[row] = ff_luts_a[row] + ff_luts_b[row] + ff_luts_p[row];

        create_row(a_size, b_size, row);

        if(row > 0) {
            for (int lut_pos = 0; lut_pos < ff_luts_p[row]; lut_pos++) {

                if (lut_pos < ff_luts_p[row-1]) {
                    add_interconnect("pipeline_p" + std::to_string(lut_pos) + "_" + std::to_string(row - 1) + "-" + std::to_string(row))
                            ->set_outpin(_name + "Slicel<" + std::to_string(row - 1) + "_" + std::to_string(lut_pos/4) + ">", letter[lut_pos%4] + outpin)
                            ->add_inpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string(lut_pos/4) + ">", letter[lut_pos%4] + "1");
                }
                else {
                    int p_lut_pos = lut_pos + ff_luts_b[row-1] + ff_luts_a[row-1] + 1;
                    add_interconnect("pipeline_p" + std::to_string(lut_pos) + "_" + std::to_string(row - 1) + "-" + std::to_string(row))
                            ->set_outpin(_name + "Slicel<" + std::to_string(row - 1) + "_" + std::to_string(p_lut_pos/4) + ">", letter[p_lut_pos%4] + outpin)
                            ->add_inpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string(lut_pos/4) + ">", letter[lut_pos%4] + "1");
                }
            }


            for(int lut_pos = 3; lut_pos < lut_count; lut_pos++) {
                add_interconnect("t<" + std::to_string(row) + "," + std::to_string(lut_pos - 3) + ">")
                        ->set_outpin(_name + "Slicel<" + std::to_string(row-1) + "_" + std::to_string((lut_pos + ff_luts[row-1])/4) + ">", letter[(lut_pos + ff_luts[row-1])%4] + outpin)
                        ->add_inpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string((lut_pos + ff_luts[row] - 2)/4) + ">", letter[(lut_pos + ff_luts[row] - 2)%4] + "1")
                        ->add_inpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string((lut_pos + ff_luts[row] - 2)/4) + ">", letter[(lut_pos + ff_luts[row] - 2)%4] + "X");
            }
        }
    }


    // adding ports for inputs
    add_ports();

    for(auto s: _slices) {
        add_interconnect("clk")->add_inpin(s.get_name(), "CLK");
    }

    add_port("clk", _slices.front().get_name(), "CLK");

    _inst_name = _slices.front().get_name();
    _multiplier_count++;
}

void Multiplier::create_row(int a_size, int b_size, int row) {
    // LUT inputs: A1: t - A2: an - A3: an-1 - A4: bm-1 - A5: bm - A6: bm+1

    bool is_last_row = row == _row_count-1;

    std::string letter[] = {"A", "B", "C", "D"};
    int ff_luts_a = _is_pipelined && !is_last_row ? a_size : 0;
    int ff_luts_b = _is_pipelined && !is_last_row ? b_size - 1 - row * 2 : 0;
    int ff_luts_p = _is_pipelined ? row * 2 : 0;
    int ff_luts = ff_luts_a + ff_luts_b + ff_luts_p;

    int lut_count = a_size + 5;
    int slice_count = (int) ceil(((double)lut_count + (double)ff_luts)/4.0);


    for(int column = 0; column < slice_count; column++) {
        int luts_left = lut_count + ff_luts - (column)*4;
        std::string slice_name = _name + "Slicel<" + std::to_string(row) + "_" + std::to_string(column) + ">";
        Slicel &current_slice = create_slice(row, column , a_size);

        // connecting a and b inputs
        int bm = row * 2;

        for(int i = 0; i < 4; i++) {
            int lut_pos = (column * 4) + i;

            // first logic lut ground connection
            if(_is_pipelined && lut_pos == ff_luts) {
                add_ground_connection(slice_name, letter[i] + "1");
                add_ground_connection(slice_name, letter[i] + "X");
            }

            // TODO: refactor
            // A inputs/pipline
            if(_is_pipelined) {
                std::string outpin_net = "pipeline_a" + std::to_string(lut_pos - ff_luts_b - ff_luts_p) + "_" + std::to_string(row) + "-" + std::to_string(row+1);
                std::string inpin_net = "pipeline_a" + std::to_string(lut_pos - ff_luts_b - ff_luts_p) + "_" + std::to_string(row-1) + "-" + std::to_string(row);

                if(!is_last_row) {
                    // a pipeline outputs
                    if((lut_pos >= ff_luts_b + ff_luts_p) && (lut_pos < ff_luts_a + ff_luts_b + ff_luts_p)) {
                        add_interconnect(outpin_net)->set_outpin(slice_name, letter[i] + "Q");
                    }
                }

                if(row == 0) {
                    if((lut_pos-2 >= ff_luts) && (lut_pos-2 < a_size + ff_luts)) {
                        add_interconnect("input_a" + std::to_string(lut_pos-ff_luts-2))->add_inpin(slice_name, letter[i] + "3");
                    }
                    if((lut_pos-1 >= ff_luts) && (lut_pos-1 < a_size + ff_luts)) {
                        add_interconnect("input_a" + std::to_string(lut_pos-ff_luts-1))->add_inpin(slice_name, letter[i] + "2");
                    }

                    // first row pipeline input
                    if((lut_pos >= ff_luts_b + ff_luts_p) && (lut_pos < a_size + ff_luts_b + ff_luts_p)) {
                        add_interconnect("input_a" + std::to_string(lut_pos - ff_luts_b - ff_luts_p))->add_inpin(slice_name, letter[i] + "1");
                    }
                } else {
                    // a pipeline inputs
                    if((lut_pos >= ff_luts_b + ff_luts_p) && (lut_pos < ff_luts_a + ff_luts_b + ff_luts_p)) {
                        add_interconnect(inpin_net)->add_inpin(slice_name, letter[i] + "1");
                    }

                    if((lut_pos-2 >= ff_luts) && (lut_pos-2 < a_size + ff_luts)) {
                        add_interconnect("pipeline_a" + std::to_string(lut_pos-ff_luts-2) + "_" + std::to_string(row-1) + "-" + std::to_string(row))->add_inpin(slice_name, letter[i] + "3");
                    }
                    if((lut_pos-1 >= ff_luts) && (lut_pos-1 < a_size + ff_luts)) {
                        add_interconnect("pipeline_a" + std::to_string(lut_pos-ff_luts-1) + "_" + std::to_string(row-1) + "-" + std::to_string(row))->add_inpin(slice_name, letter[i] + "2");
                    }
                }
            }
            else {
                if(lut_pos-2 >= ff_luts && lut_pos-2 < (a_size + ff_luts)) {
                    add_interconnect("input_a" + std::to_string(lut_pos-ff_luts-2))->add_inpin(slice_name, letter[i] + "3");
                }
                if(lut_pos-1 >= ff_luts && lut_pos-1 < (a_size + ff_luts)) {
                    add_interconnect("input_a" + std::to_string(lut_pos-ff_luts-1))->add_inpin(slice_name, letter[i] + "2");
                }
            }

            // a input ground connections on first two logic luts
            if(lut_pos - ff_luts == 0) {
                add_ground_connection(slice_name, letter[i] + "2");
                add_ground_connection(slice_name, letter[i] + "3");
            }
            if(lut_pos - ff_luts == 1) {
                add_ground_connection(slice_name, letter[i] + "3");
            }

            // B inputs/pipeline
            if(_is_pipelined) {
                std::string outpin_net = "pipeline_b" + std::to_string(lut_pos - ff_luts_p + 1 + 2 * row) + "_" + std::to_string(row) + "-" + std::to_string(row+1);
                std::string inpin_net = "pipeline_b" + std::to_string(lut_pos - ff_luts_p + 1 + 2 * row) + "_" + std::to_string(row-1) + "-" + std::to_string(row);

                if(!is_last_row) {
                    if((lut_pos >= ff_luts_p) && (lut_pos < ff_luts_b + ff_luts_p)) {
                        add_interconnect(outpin_net)->set_outpin(slice_name, letter[i] + "Q");
                    }
                }

                if(row == 0) {
                    if(lut_pos >= ff_luts && lut_pos < lut_count + ff_luts - 2) {
                        // generate b inputs
                        for(int j = 0; j < 3; j++) {
                            int b = bm + j - 1;
                            if (b >= 0 && b < b_size) {
                                add_interconnect("input_b" + std::to_string(b))->add_inpin(slice_name, letter[i] + std::to_string(4 + j));
                            }
                            else {
                                add_ground_connection(slice_name, letter[i] + std::to_string(4 + j));
                            }
                        }
                    }

                    // first row pipeline input
                    if((lut_pos >= ff_luts_p) && (lut_pos < ff_luts_b + ff_luts_p)) {
                        add_interconnect("input_b" + std::to_string(lut_pos - ff_luts_p + 1 + 2 * row))->add_inpin(slice_name, letter[i] + "1");
                    }
                }
                else {
                    // b pipeline inputs
                    if((lut_pos >= ff_luts_p) && (lut_pos < ff_luts_b + ff_luts_p)) {
                        add_interconnect(inpin_net)->add_inpin(slice_name, letter[i] + "1");
                    }

                    if(lut_pos >= ff_luts && lut_pos < lut_count + ff_luts - 2) {
                        for(int j = 0; j < 3; j++) {
                            int b = bm + j - 1;
                            if (b >= 0 && b < b_size) {
                                add_interconnect("pipeline_b" + std::to_string(b) + "_" + std::to_string(row-1) + "-" + std::to_string(row))->add_inpin(slice_name, letter[i] + std::to_string(4 + j));
                            }
                            else {
                                add_ground_connection(slice_name, letter[i] + std::to_string(4 + j));
                            }
                        }
                    }
                }
            }
            else {
                // last 2 LUTs don't need b inputs
                if(lut_pos >= ff_luts && lut_pos < lut_count + ff_luts - 2) {
                    // generate b inputs
                    for(int j = 0; j < 3; j++) {
                        int b = bm + j - 1;
                        if (b >= 0 && b < b_size) {
                            add_interconnect("input_b" + std::to_string(b))->add_inpin(slice_name, letter[i] + std::to_string(4 + j));
                        }
                        else {
                            add_ground_connection(slice_name, letter[i] + std::to_string(4 + j));
                        }
                    }
                }
            }

            // X input for pipeline luts
            if(_is_pipelined && lut_pos < ff_luts) {
                add_vcc_connection(slice_name, letter[i] + "X");
            }


            if(_is_pipelined) {
                if(is_last_row) {
                    if (lut_pos < ff_luts_p) {
                        add_interconnect("output_p" + std::to_string(lut_pos))->set_outpin(slice_name, letter[i] + "Q");
                    } else if (lut_pos > ff_luts && lut_pos <= (a_size + b_size)) {
                        add_interconnect("output_p" + std::to_string(lut_pos - 1))->set_outpin(slice_name,
                                                                                               letter[i] + "Q");
                    }
                }
            }
            else {
                int output_pos = (row * 2) + lut_pos - ff_luts - 1;
                if(lut_pos > 0 && (lut_pos <= 2 || (output_pos < (a_size+b_size) && is_last_row))) {
                    add_interconnect("output_p" + std::to_string(output_pos))->set_outpin(slice_name, letter[i] + "MUX");
                }
            }


            if(luts_left - i == 4) {    // last A LUT
                add_ground_connection(slice_name, letter[i] + "2"); // input a(n) in last A LUT
                if(row == 0) {
                    add_ground_connection(slice_name, letter[i] + "1");
                    add_ground_connection(slice_name, letter[i] + "X");
                }
            }
            else if(luts_left - i == 3) {   // B LUT
                if(row == 0) {
                    add_vcc_connection(slice_name, letter[i] + "1"); // input t in first row B LUT
                    add_vcc_connection(slice_name, letter[i] + "X");
                }
            }
            else if(luts_left - i == 2) {   // C LUT
                add_vcc_connection(slice_name, letter[i] + "1"); // input t
                add_vcc_connection(slice_name, letter[i] + "X");
            }
            else if(luts_left - i == 1) {   // C LUT for carry routing
                add_ground_connection(slice_name, letter[i] + "1");
                //add_ground_connection(slice_name, letter[i] + "X");
            }
            else if(luts_left - i > 0) {
                if(row == 0 && lut_pos > ff_luts) {
                    add_ground_connection(slice_name, letter[i] + "1");
                    add_ground_connection(slice_name, letter[i] + "X");
                }
            }
        }

        if(column == 0) {
            current_slice.set_attribute("PRECYINIT", "1");
        }
        else {
            add_interconnect(_name + "carry<" + std::to_string(row) + "_" + std::to_string(column-1) + "-" +  std::to_string(column) + ">")
                    ->set_outpin(_name + "Slicel<" + std::to_string(row) + "_" + std::to_string(column-1) + ">", "COUT")
                    ->add_inpin(slice_name, "CIN");
        }
    }
}

void Multiplier::add_ports() {
    for (auto n: _net) {
        if((n.second.get_name().find("input_") != std::string::npos)
            || (n.second.get_name().find("output_") != std::string::npos)) {

             size_t underscore_pos = n.second.get_name().find("_") + 1;

            if(!n.second.get_outpin().empty()) {
                add_port(n.second.get_name().substr(underscore_pos, std::string::npos),
                         n.second.get_outpin().get_instance(),
                         n.second.get_outpin().get_pin());
            }
            else {
                if(!n.second.get_inpins().empty()) {
                    n.second.get_inpins().at(0);
                    add_port(n.second.get_name().substr(underscore_pos, std::string::npos),
                             n.second.get_inpins().at(0).get_instance(),
                             n.second.get_inpins().at(0).get_pin());
                }
            }
        }
    }
}

void Multiplier::place(int x_pos, int y_pos, Device &device) {
    size_t pos = 0;

    // the multiplier is rotated 90 degrees to fit the carry chain, so rows and columns are swapped
    for(int x = 0; x < _row_count; ++x) {
        int ff__luts_a = _is_pipelined && x<_row_count-1 ? _a_size : 0;
        int ff_luts_b = _is_pipelined && x<_row_count-1 ? _b_size - 1 - x * 2 : 0;
        int ff_luts = _is_pipelined ? (x * 2 + ff__luts_a + ff_luts_b) : 0;
        int lut_count = _a_size + 5;
        int slice_count = (int) ceil(((double)lut_count + (double)ff_luts)/4.0);

        for (int y = 0; y < slice_count; ++y) {
            _slices.at(pos).set_primitive_site(device.get_slice(x + x_pos, y + y_pos));
            _slices.at(pos).set_placed(true);
            pos++;
        }
    }
}

Slicel &Multiplier::create_slice(int row, int column, int a_size) {
    int ff__luts_a = _is_pipelined && row<_row_count-1 ? a_size : 0;
    int ff_luts_b = _is_pipelined && row<_row_count-1 ? _b_size - 1 - row * 2 : 0;
    int ff_luts = _is_pipelined ? (row * 2 + ff__luts_a + ff_luts_b) : 0;
    int luts_left = (a_size + 5 + ff_luts) - (column)*4;

    std::string slice_name = _name + "Slicel<" + std::to_string(row) + "_" + std::to_string(column) + ">";
    _slices.emplace_back(slice_name);
    Slicel &current_slice = _slices.back();

    // enable carry output if there will be more slices in this row
    if(luts_left > 4) {
        current_slice.set_attribute("COUTUSED", "0");
    }


    // booth en/dec
    std::string a_lut = "((~A3*((~A2*(((~A4*A6)+(A4*(~A5*A6)))@A1))+(A2*((~A4*(A5@(A6@A1)))+(A4*(((~A5*A6)+A5)@~A1))))))+(A3*((~A2*((~A4*((A5*A6)@A1))+(A4*(A5@(A6@A1)))))+(A2*(((~A4*(~A5+(A5*A6)))+(A4*A6))@~A1)))))";
    // not(compl) add configuration
    std::string b_lut = "(((~A4*A6)+(A4*(~A5*A6)))@~A1)";
    // simple adder
    std::string c_lut = "A1";

    std::string letter[] = {"A", "B", "C", "D"};

    for (int i = 0; i < 4; i++) {
        int lut_pos = (column * 4) + i;
        std::string lut_config = a_lut;

        if(luts_left - i == 3) {
            lut_config = b_lut;
        }
        else if(luts_left - i == 2 || luts_left - i == 1) {
            lut_config = c_lut;
        }


        if(_is_pipelined && lut_pos < ff_luts) {
            current_slice.set_attribute(letter[i] + "6LUT", c_lut);
            current_slice.set_attribute(letter[i] + "6LUTNAME", "pipeline<" + std::to_string(row) + "_" + std::to_string(lut_pos) + ">");
            current_slice.set_attribute(letter[i] + "CY0", letter[i] + "X");
            current_slice.set_attribute(letter[i] + "FFMUX", "O6");
            current_slice.set_attribute(letter[i] + "FF", "#FF");
            current_slice.set_attribute(letter[i] + "FFNAME", "pipelineff<" + std::to_string(row) + "_" + std::to_string(lut_pos) + ">");

        }
        else if(luts_left - i > 0) {
            current_slice.set_attribute(letter[i] + "6LUT", lut_config);
            current_slice.set_attribute(letter[i] + "6LUTNAME", "logic<" + std::to_string(row) + "_" + std::to_string(lut_pos - ff_luts) + ">");
            current_slice.set_attribute(letter[i] + "CY0", letter[i] + "X");

            if(_is_pipelined) {
                current_slice.set_attribute(letter[i] + "FF", "#FF");
                current_slice.set_attribute(letter[i] + "FFNAME", "logicff<" + std::to_string(row) + "_" + std::to_string(lut_pos - ff_luts) + ">");
                current_slice.set_attribute(letter[i] + "FFMUX", "XOR");
            }
            else {
                current_slice.set_attribute(letter[i] + "OUTMUX", "XOR");
            }
        }

        if(_is_pipelined) {
            current_slice.set_attribute("SYNC_ATTR", "SYNC");
            current_slice.set_attribute("CLKINV", "CLK");
        }
    }

    return _slices.back();
}

