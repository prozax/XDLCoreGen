#include <iostream>
#include "AddSub.h"
#include "Design.h"
#include "Multiplier.h"

using namespace std;

int main() {
    //Slicel test_slicel = Slicel("TEST");
    Device d = Device("xc6vlx75tff484-3", "./devices/xc6vlx75tff484-3.xdl");
    //cout<<d;
    AddSub test_addsub = AddSub(32);
    Multiplier test_multi = Multiplier(8, 8);
    Design test_design = Design("testdesign", d);
    test_design.add_module(test_multi);
    test_design.place();


    //cout << test_slicel.to_string() << endl;
    //cout << "\n AddSub:\n" << endl << test_addsub.to_string();
    cout << test_design.to_string();

    /*
    ofstream outfile;
    outfile.open("C:\\Users\\prozac\\xdl\\test.xdl");
    outfile<<test_design.to_string();
    outfile.close();
     */


    return 0;
}