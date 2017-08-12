
#ifndef XDLCOREGEN_MULTIPLIER_H
#define XDLCOREGEN_MULTIPLIER_H


#include "Module.h"
#include "Device.h"

class Multiplier: public Module {
protected:
    //std::vector<Slicel> _slices;
    static int _multiplier_count;
    int _row_count;

public:
    Multiplier(int, int);
    void create_row(int a_size, int b_size, int row);

    void place(int x_pos, int y_pos, Device &device) override;
};


#endif //XDLCOREGEN_MULTIPLIER_H
