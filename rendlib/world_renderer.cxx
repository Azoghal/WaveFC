#include <iostream>
#include "world_renderer.hxx"

namespace renderer{

std::map<int, char> WorldRenderer::sizemap_ =  {{0, '.'}, {1, '+'}, {2, 'o'}, {3, 'O'}};

WorldRenderer::WorldRenderer(int width, int height, std::string character_set)
{
    // Constructor
    width_ = width;
    height_ = height;
}

WorldRenderer::~WorldRenderer()
{
    // Destructor
}

void WorldRenderer::PrintWorld()
{
    std::vector<std::vector<int>>::iterator row;
    for(auto& row:world_map_){
        for(auto& col:row){
            std::cout << colourmap_[col] << sizemap_[0] << ' ' << colourmap_[0];
        }
        std::cout << std::endl;
    }
}

void WorldRenderer::SetWorld(){
    std::cout << "Setting empty map" << std::endl;
    std::vector<std::vector<int>> empty_map(height_,std::vector<int>(width_,0));
    world_map_ = empty_map;
}

void WorldRenderer::SetWorld(std::vector<std::vector<int>> map){
    int w = map.size();
    int h = map[0].size();
    std::cout << "Setting map of size" << w << "x" << h << std::endl;
    world_map_ = map;
}

void WorldRenderer::SetColourmap(){
    std::cout << "Setting colourmap" << std::endl;
    colourmap_[0] = "\033[0m";
    colourmap_[1] = "\033[34m";
    colourmap_[2] = "\033[35m";
    colourmap_[3] = "\033[36m";

}

} // namespace renderer

namespace {
    /* If no references outside of file */
    /* Can also declare them static */
} // namespace

