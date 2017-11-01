
#ifndef XDLCOREGEN_MULTIPLIER_H
#define XDLCOREGEN_MULTIPLIER_H


#include "Module.h"
#include "Device.h"

class Multiplier: public Module {
protected:
    static int _multiplier_count;
    int _row_count;
    int _a_size;
    int _b_size;
    bool _is_pipelined;

    void create_row(int a_size, int b_size, int row);
    void add_input_ports();
    Slicel &create_slice(int row, int column, int a_size);

public:
    Multiplier(int, int, bool);
    void place(int x_pos, int y_pos, Device &device) override;
};


#endif //XDLCOREGEN_MULTIPLIER_H
