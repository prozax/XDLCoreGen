#include <iostream>
#include <cstdlib>
#include "Slicel.h"
#include "AddSub.h"

using namespace std;

int main() {
    Slicel test_slicel = Slicel("TEST");
    AddSub test_addsub = AddSub(32);
    //cout << test_slicel.to_string() << endl;
    cout << "\n AddSub:\n" << endl << test_addsub.to_string();
    return 0;
}