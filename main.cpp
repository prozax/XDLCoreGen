#include <iostream>
#include <fstream>
#include "Design.h"
#include "Multiplier.h"
#include "cxxopts.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    cxxopts::Options options("XDLCoreGen", "Creates a XDL description of a multiplier.");

    int a_size = 8;
    int b_size = 8;
    bool is_pipelined = false;


    options.add_options()
            ("a,a_length", "A input length. Default: 8", cxxopts::value<int>(), "N")
            ("b,b_length", "B input length. Default: 8", cxxopts::value<int>(), "N")
            ("o,output", "Output file path. If omitted the output will be printed.", cxxopts::value<std::string>(), "<path>")
            ("p,pipelined", "Generate pipelined multiplier. Default: not pipelined")
            ("h,help", "Print help")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help({""}) << std::endl;
        return 0;
    }

    if(result.count("a")) {
        a_size = result["a"].as<int>();
    }

    if(result.count("b")) {
        b_size = result["b"].as<int>();
    }

    is_pipelined = (result.count("p") != 0);

    Device d = Device("xc6vlx75tff484-3", "./devices/xc6vlx75tff484-3.xdl");
    Multiplier test_multi = Multiplier(a_size, b_size, is_pipelined);
    Design test_design = Design("__XILINX_NMC_MACRO", d);
    test_design.add_module(test_multi);
    test_design.place();


    if(result.count("output")) {
        ofstream outfile;
        outfile.open(result["output"].as<std::string>());
        outfile << test_design;
        outfile.close();
    }
    else {
        cout << test_design;
    }


    return 0;
}