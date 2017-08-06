
#ifndef XDLCOREGEN_MULTIPLIER_H
#define XDLCOREGEN_MULTIPLIER_H


#include "Module.h"

class Multiplier: public Module {
protected:
    //std::vector<Slicel> _slices;
    static int _multiplier_count;
    int _row_count;

public:
    Multiplier(int, int);
    void create_row(int b_size, int row);
};


#endif //XDLCOREGEN_MULTIPLIER_H
