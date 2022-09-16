#include <iostream>
#include <sstream>
#include <time.h> 

#include "world_renderer.hxx"
#include "wave_function_collapse.hxx"
#include "parser.hxx"

namespace argparsing{
    int arg_to_int(std::string arg){
        std::istringstream arg_int(arg);
        int val;
        if (arg_int >> val)
        {
            return val;
        }
        return 0;
    }

    bool keyword_to_bool(std::string exp_keyword, std::string keyword, bool default_val){
        if (keyword == exp_keyword){
            return !default_val;
        }
        return default_val;
    }

    bool keyword_to_bool(std::string exp_keyword, std::string keyword){
        return keyword_to_bool(exp_keyword, keyword, false);
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 3 && argc != 4){
        std::cout << "Usage: " << argv[0] << " [width] [height] [[--wait]]" << std::endl;
        return 1;
    }
    srand(time(NULL));

    int w = argparsing::arg_to_int(argv[1]);
    int h = argparsing::arg_to_int(argv[2]);
    bool wait_for_input = false;
    if (argc == 4){
        // If add more keyword arguments, loop over each passed pair and query for matching each expected
        wait_for_input = argparsing::keyword_to_bool("--wait", argv[3]);
    }
    std::vector<std::vector<int>> to_parse = {{1,0,1,0},{0,1,0,1},{1,0,1,0},{0,1,0,1}};
    wfc::Parser WaveParse(to_parse, 3);
    WaveParse.Parse();
    wfc::Constraints constraints = WaveParse.GetConstraints();
    std::map<int,int> state_distro = WaveParse.GetStateDistribution();
    
    renderer::WorldRenderer WaveRend(w, h);
    // rendererObject.PrintWorld();

    wfc::WaveFunctionCollapse WaveFC(w, h, constraints, state_distro);
    WaveFC.AddRenderer(&WaveRend);
    WaveFC.Collapse(wait_for_input);
    return 0;
}
