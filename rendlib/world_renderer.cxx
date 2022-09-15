#include <iostream>
#include "world_renderer.hxx"

namespace renderer{

std::map<int, char> WorldRenderer::sizemap_ =  {{-1,'_'}, {0, '-'}, {1, '+'}, {2, 'o'}, {3, 'O'}};

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
            std::cout << colourmap_[item] << sizemap_[item] << " " << colourmap_[-1];
        }
        std::cout << std::endl;
    }
}

void WorldRenderer::SetWorld(){
    std::cout << "Setting empty map" << std::endl;
    world_map_ = std::vector<std::vector<int>>(height_,std::vector<int>(width_,0));
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

