
#ifndef XDLCOREGEN_MULTIPLIER_H
#define XDLCOREGEN_MULTIPLIER_H


#include "Module.h"
#include "Device.h"

class Multiplier: public Module {
protected:
    int _row_count; /**< Number of rows the multiplier useses. */
    int _a_size; /**< Number of a input bits. */
    int _b_size; /**< Number of b input bits. */
    bool _is_pipelined; /**< Pipelining switch. */

    void create_row(int a_size, int b_size, int row);
    void connect_rows(int row);
    void add_ports();
    Slicel &create_slice(int row, int column, int a_size);

public:
    Multiplier(int, int, bool);
    void place(int x_offset, int y_offset, Device &device) override;
};


#endif //XDLCOREGEN_MULTIPLIER_H
