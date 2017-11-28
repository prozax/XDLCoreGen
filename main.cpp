#include <iostream>
#include <fstream>
#include "Design.h"
#include "Multiplier.h"
#include "cxxopts.hpp"
#include "examples/Example.h"

using namespace std;

int main(int argc, char* argv[]) {
    cxxopts::Options options("XDLCoreGen", "Creates a XDL description of a multiplier.");

    int a_size = 8;
    int b_size = 8;
    int x_offset = 0;
    int y_offset = 0;
    bool is_pipelined = false;
    string device_path;

    options.add_options()
            ("a,a_length", "A input length. Default: 8", cxxopts::value<int>(), "N")
            ("b,b_length", "B input length. Default: 8", cxxopts::value<int>(), "N")
            ("d,device_file", "Device file path.", cxxopts::value<std::string>(), "<path>")
            ("o,output", "Output file path. If omitted the output will be printed.", cxxopts::value<std::string>(), "<path>")
            ("p,pipelined", "Generate pipelined multiplier. Default: not pipelined")
            ("x,x_offset", "X offset for the placer. Default: 0", cxxopts::value<int>(), "N")
            ("y,y_offset", "Y offset for the placer. Default: 0", cxxopts::value<int>(), "N")
            ("h,help", "Print help")
            ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help({""}) << std::endl;
        return 0;
    }

    if(result.count("device_file")) {
        device_path = result["device_file"].as<string>();
        if(!ifstream(device_path)) {
            cout<< "Error: device file not found.";
            return 0;
        }
    }

    if(result.count("a_length")) {
        a_size = result["a_length"].as<int>();
    }

    if(result.count("b_length")) {
        b_size = result["b_length"].as<int>();
    }

    if(result.count("x_offset")) {
        x_offset = result["x_offset"].as<int>();
    }

    if(result.count("y_offset")) {
        y_offset = result["y_offset"].as<int>();
    }

    is_pipelined = (result.count("pipelined") != 0);

    Device d = Device("./devices/xc6vlx75tff484-3.xdl");

    Multiplier m = Multiplier(a_size, b_size, is_pipelined);
    Design design = Design(d);
    design.add_module(m);
    design.place(x_offset, y_offset);

//    Example e = Example();

    if(result.count("output")) {
        ofstream outfile;
        outfile.open(result["output"].as<string>());
        outfile << design;
        outfile.close();
    }
    else {
        cout << design;
    }




    return 0;
}