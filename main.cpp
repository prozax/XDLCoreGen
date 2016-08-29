#include <iostream>
#include <cstdlib>
#include "Slicel.h"

using namespace std;

int main() {
    Slicel test_slicel = Slicel("TEST");
    cout << test_slicel.to_string() << endl;
    return 0;
}