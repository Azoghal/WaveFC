#include <iostream>
#include "world_renderer.hxx"

namespace renderer{

std::unordered_map<int, char> WorldRenderer::sizemap_ =  {{-1,'_'}, {0, '-'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5,'5'}, {6,'6'}, {7,'7'}, {8,'8'}};
// std::unordered_map<int, char> WorldRenderer::sizemap_ =  {{-1,'_'}, {0, '-'}, {1, '~'}, {2, 'o'}, {3, '0'}, {4, '#'}, {5,'@'}, {6,'6'}, {7,'7'}, {8,'8'}};

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
    int h = map.size();
    int w = map[0].size();
    world_map_ = map;
}

void WorldRenderer::SetColourmap(){
    colourmap_[-1] = "\033[0m";
    colourmap_[0] = "\033[36m";
    colourmap_[1] = "\033[32m";
    colourmap_[2] = "\033[31m";
    colourmap_[3] = "\033[35m";
    colourmap_[4] = "\033[34m";
    colourmap_[5] = "\033[33m";
    colourmap_[6] = "\033[90m";
    colourmap_[7] = "\033[91m";
    colourmap_[8] = "\033[92m";
    colourmap_[9] = "\033[93m";

}

} // namespace renderer

namespace {
    /* If no references outside of file */
    /* Can also declare them static */
} // namespace

