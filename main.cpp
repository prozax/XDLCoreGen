#include <iostream>
#include <cstdlib>
#include "Slicel.h"
#include "AddSub.h"
#include "Design.h"

using namespace std;

int main() {
    //Slicel test_slicel = Slicel("TEST");
    AddSub test_addsub = AddSub(32);
    Design test_design = Design("testdesign", "xc6vlx75tff484-3");
    test_design.add_module(test_addsub);
    //cout << test_slicel.to_string() << endl;
    //cout << "\n AddSub:\n" << endl << test_addsub.to_string();
    cout<<test_design.to_string();
    return 0;
}