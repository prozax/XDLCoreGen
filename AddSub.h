#ifndef XDLCOREGEN_ADDSUB_H
#define XDLCOREGEN_ADDSUB_H

#include <string>
#include "Module.h"

class AddSub: public Module {
private:

public:
    AddSub(int bit_count);

    void place(int x, int y, Device &device) override;

    //AddSub();

};


#endif //XDLCOREGEN_ADDER_H
