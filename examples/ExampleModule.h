
#ifndef XDLCOREGEN_EXAMPLEMODULE_H
#define XDLCOREGEN_EXAMPLEMODULE_H


#include "../Module.h"

class ExampleModule: public Module  {
public:
    ExampleModule();
    void place(int x_offset, int y_offset, Device &device);
};


#endif //XDLCOREGEN_EXAMPLEMODULE_H
