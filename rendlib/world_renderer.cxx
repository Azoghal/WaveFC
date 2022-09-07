#include <iostream>
#include "world_renderer.hxx"

namespace renderer{

std::map<int, char> WorldRenderer::sizemap_ =  {{0, '-'}, {1, '+'}, {2, 'o'}, {3, 'O'}, {4,' '}};

WorldRenderer::WorldRenderer(int width, int height, std::string character_set)
{
    // Constructor
    width_ = width;
    height_ = height;
    this->SetWorld();
    this->SetColourmap();
}

WorldRenderer::~WorldRenderer()
{
    // Destructor
}

void WorldRenderer::PrintWorld()
{
    //std::vector<std::vector<int>>::iterator row;
    for(auto& row:world_map_){
        for(auto& item:row){
            std::cout << colourmap_[0] << sizemap_[item] << colourmap_[0];
        }
        std::cout << std::endl;
    }
}

void WorldRenderer::SetWorld(){
    std::cout << "Setting empty map" << std::endl;
    world_map_ = std::vector<std::vector<int>>(height_,std::vector<int>(width_,0));
    // TODO remove
    for (int i=0; i<width_; ++i){
        world_map_[0][i]=2;
        world_map_[1][i]=1;
    }
}

void WorldRenderer::SetWorld(std::vector<std::vector<int>> map){
    int w = map.size();
    int h = map[0].size();
    std::cout << "Setting map of size" << w << "x" << h << std::endl;
    for(auto row:map){
        for(auto num:row){
            std::cout << num;
        }
        std::cout << std::endl;
    }
    world_map_ = map;
    std::cout << "Reached the end of setworld" << std::endl;
}

void WorldRenderer::SetColourmap(){
    std::cout << "Setting colourmap" << std::endl;
    colourmap_[0] = "\033[0m";
    colourmap_[1] = "\033[36m";
    colourmap_[2] = "\033[32m";
    colourmap_[3] = "\033[31m";
}

} // namespace renderer

namespace {
    /* If no references outside of file */
    /* Can also declare them static */
} // namespace

