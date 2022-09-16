#include <iostream>
#include "world_renderer.hxx"

namespace renderer{

std::unordered_map<int, char> WorldRenderer::sizemap_ =  {{-1,'_'}, {0, '-'}, {1, '+'}, {2, 'o'}, {3, 'O'}};

WorldRenderer::WorldRenderer(int width, int height)
{
    width_ = width;
    height_ = height;
    this->SetColourmap();
    this->SetWorld();
}

void WorldRenderer::PrintWorld()
{
    // For each location, add ANSI colour, relevant glyph, escape ANSI colour.
    for(auto& row:world_map_){
        for(auto& item:row){
            std::cout << colourmap_[item] << sizemap_[item] << " " << colourmap_[-1];
        }
        std::cout << std::endl;
    }
}

void WorldRenderer::SetWorld(){
    // Set an empty world.
    world_map_ = std::vector<std::vector<int>>(height_,std::vector<int>(width_,0));
}

void WorldRenderer::SetWorld(std::vector<std::vector<int>> map){
    // Set a non empty world.
    int w = map.size();
    int h = map[0].size();
    for(auto row:map){
        for(auto num:row){
            std::cout << num;
        }
        std::cout << std::endl;
    }
    world_map_ = map;
}

void WorldRenderer::SetColourmap(){
    colourmap_[-1] = "\033[0m";
    colourmap_[0] = "\033[36m";
    colourmap_[1] = "\033[32m";
    colourmap_[2] = "\033[31m";
    colourmap_[3] = "\033[35m";
}

} // namespace renderer

namespace {
    /* If no references outside of file */
    /* Can also declare them static */
} // namespace

