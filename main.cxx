#include <iostream>
#include <sstream>
#include <time.h> 

#include "world_renderer.hxx"
#include "wave_function_collapse.hxx"
#include "parser.hxx"

namespace argparsing{
    int argToInt(std::string arg){
        std::istringstream arg_int(arg);
        int val;
        if (arg_int >> val)
        {
            return val;
        }
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 3){
        std::cout << "Usage: " << argv[0] << " [width] [height]" << std::endl;
        return 1;
    }

    srand(time(NULL));

    int w = argparsing::argToInt(argv[1]);
    int h = argparsing::argToInt(argv[2]);
    std::vector<std::vector<int>> to_parse = {{0,0,0,0},{1,1,1,1},{0,0,0,0},{1,1,1,1}};
    wfc::Parser WaveParse(to_parse, 3);
    wfc::Constraints constraints = WaveParse.Parse();
    renderer::WorldRenderer WaveRend(w, h, "A");
    // rendererObject.PrintWorld();

    wfc::WaveFunctionCollapse WaveFC(w, h, 3, constraints);
    WaveFC.AddRenderer(&WaveRend);
    WaveFC.Collapse();
    return 0;
}
