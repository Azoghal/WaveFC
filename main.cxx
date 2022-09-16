#include <iostream>
#include <sstream>
#include <time.h> 

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
}

int main(int argc, char const *argv[])
{
    if (argc != 3 && argc != 4){
        std::cout << "Usage: " << argv[0] << " [width] [height] [[--wait]]" << std::endl;
        return 1;
    }

    // Set random seed for state collapse
    srand(time(NULL));

    // Parse CLI arguments
    int w = argparsing::arg_to_int(argv[1]);
    int h = argparsing::arg_to_int(argv[2]);
    bool wait_for_input = false;
    if (argc == 4){
        // If add more keyword arguments, loop over each passed pair and query for matching each expected
        wait_for_input = argparsing::keyword_to_bool("--wait", argv[3]);
    }

    // Load source image as 2d int vector
    std::vector<std::vector<int>> to_parse = {{1,0,1,0},{0,1,0,1},{1,0,1,0},{0,1,0,1}};

    // Parse source image and extract information
    wfc::Parser WaveParse(to_parse, 3);
    WaveParse.Parse();
    wfc::Constraints constraints = WaveParse.GetConstraints();
    std::unordered_map<int,int> state_distro = WaveParse.GetStateDistribution();
    
    // Setup renderer
    renderer::WorldRenderer WaveRend(w, h);

    // Setup WFC and begin collapse
    wfc::WaveFunctionCollapse WaveFC(w, h, constraints, state_distro);
    WaveFC.AddRenderer(&WaveRend);
    WaveFC.Collapse(wait_for_input);
    return 0;
}
