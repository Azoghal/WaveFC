#include <iostream>
#include <sstream>
#include <time.h> 
#include <exception>

#include "world_renderer.hxx"
#include "wave_function_collapse.hxx"
#include "parser.hxx"

namespace argparsing{
    int arg_to_int(std::string arg){
        // Parse string arg to int
        std::istringstream arg_int(arg);
        int val;
        if (arg_int >> val)
        {
            return val;
        }
        return 0;
    }

    bool keyword_to_bool(std::string exp_keyword, std::string keyword, bool val_if_present){
        // Parse keyword argument to bool
        // val_if_present : bool that corresponds to keyword presence
        if (keyword == exp_keyword){
            return val_if_present;
        }
        return !val_if_present;
    }

    bool keyword_to_bool(std::string exp_keyword, std::string keyword){
        // Parse keyword argument to bool
        // Presence of keyword results in true.
        return keyword_to_bool(exp_keyword, keyword, true);
    }

    void PrintUsage(std::string name){
        std::cerr << "Usage: " << std::endl;
        std::cerr << name << " parse [parse source] [wave width in kernels] [wave height in kernels] [kernel-size] [[--wait] [--save]]" << std::endl;
        std::cerr << name << " load [load source] [wave width] [wave height] [[--wait]]" << std::endl;
    } 
}

int main(int argc, char const *argv[])
{
    if (argc == 1){
        argparsing::PrintUsage(argv[0]);
        return 1;
    }
    // Set random seed for state collapse
    srand(time(NULL));

    int w,h,kernel_size;
    std::string input_file;
    bool wait_for_input = false, save_constraints = false;


    wfc::Parser WaveParse;
    wfc::Constraints constraints;
    std::map<int, wfc::Pattern> patterns;

    // Parse CLI arguments
    std::string action = argv[1];
    if (action == "parse"){
        if (argc < 6 || argc > 8){
            argparsing::PrintUsage(std::string(argv[0]));
        }
        input_file = argv[2];
        w = argparsing::arg_to_int(argv[3]);
        h = argparsing::arg_to_int(argv[4]);
        kernel_size = argparsing::arg_to_int(argv[5]);
        if (argc > 6){
            for (int i=6; i<argc; ++i){
                wait_for_input = wait_for_input | (argv[i] == std::string("--wait"));
                save_constraints = save_constraints | (argv[i] == std::string("--save"));
            }
        }
        try {
            WaveParse.Parse(input_file, kernel_size, save_constraints);
            constraints = WaveParse.GetConstraints();
            patterns = WaveParse.GetPatterns();
        }
        catch (std::invalid_argument& e){
            std::cerr << e.what() << std::endl;
            argparsing::PrintUsage(argv[0]);
            return 1;
        }
    }
    else if (action == "load"){
        if (argc < 5 || argc > 6){
            argparsing::PrintUsage(std::string(argv[0]));
        }
        input_file = argv[2];
        w = argparsing::arg_to_int(argv[3]);
        h = argparsing::arg_to_int(argv[4]);
        std::cout << "width and height " << w << " " << h << std::endl;
        if (argc > 5){
            for (int i=5; i<argc; ++i){
                wait_for_input = wait_for_input | (argv[i] == std::string("--wait"));
            }
        }
        try {
            WaveParse.LoadParse(input_file);
            constraints = WaveParse.GetConstraints();
            patterns = WaveParse.GetPatterns();
            kernel_size = WaveParse.GetKernelSize();
        }
        catch (std::invalid_argument& e){
            std::cerr << e.what() << std::endl;
            argparsing::PrintUsage(argv[0]);
            return 1;
        }   
    }
    else{
        argparsing::PrintUsage(argv[0]);
        return 1;
    }

    // Setup renderer
    renderer::WorldRenderer WaveRend(w, h);

    // Setup WFC and begin collapse
    wfc::WaveFunctionCollapse WaveFC(w, h, kernel_size, constraints, patterns);
    WaveFC.AddRenderer(&WaveRend);
    WaveFC.Collapse(wait_for_input);
    return 0;
}
