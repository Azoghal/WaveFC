#include "wave_function_collapse.hxx"
#include <limits>
#include <stdlib.h>

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(int width, int height, int num_states, Constraints constraints)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
    width_ = width;
    height_ = height;
    constraints_ = constraints;
    num_states_ = num_states;
    this->SetupTiles();
    lowest_tile_ = nullptr;
    renderer_ = nullptr;
}

WaveFunctionCollapse::~WaveFunctionCollapse()
{
    // destructor
}

void WaveFunctionCollapse::SetupTiles(){
    world_ = std::vector<std::vector<Tile>>(width_, std::vector<Tile>(height_, Tile(num_states_, &constraints_)));
    // set neighbours of tiles
    // calculate all their entropies and store minimum
    // options: loop neighbours around
    // setup fake neighbours
    for(int y=0; y<height_; ++y){
        for(int x=0; x<width_; ++x){
            std::vector<std::vector<Tile*>> neighbours(3,std::vector<Tile*>(3,nullptr));
            for (int j=-1; j<2; ++j){
                for (int i=-1; i<2; ++i){
                    int xx = (x + i + width_) % width_;
                    int yy = (y + j + height_) % height_;
                    neighbours[i+1][j+1] = &world_[xx][yy];
                }
            }
            world_[x][y].SetNeighbours(neighbours);
            world_[x][y].UpdateEntropy();
            
        }
    }
}

int WaveFunctionCollapse::CollapseOnce(){
    std::cout << "Collapsing once" << std::endl;
    int next = this->FindLowestEntropy();
    switch (next){
        case 0:
            std::cout << "Lowest Entropy" << lowest_tile_->GetEntropy() << std::endl;
            lowest_tile_->CollapseState();
            this->Propagate(lowest_tile_);
            return 0;
        case 1:
            std::cout << "All tiles are collapsed" << std::endl;
            return 1;
        case 2:
            std::cout << "Contradiction reached" << std::endl;
            return 2;
        default:
            std::cout << "Unexepcted return code from FindLowestEntropy()" << std::endl;
            return 3;
    }
}

int WaveFunctionCollapse::Collapse(){
    int result = 0;
    while(result == 0){
        if (renderer_){
            std::vector<std::vector<int>> int_world = this->PrepareRenderWorld();
            std::cout << "Thing 1" << std::endl;
            renderer_->SetWorld(int_world);
            std::cout << "Thing 2" << std::endl;
            renderer_->PrintWorld();
            std::cin.ignore();
        }
        result = this->CollapseOnce();
    }
    if (result == 1){
        return 0;
    }
    else{
        return 1;
    }
    // for(auto& row:world_){
    //     for(auto& tile:row){
    //         if (tile.IsCollapsed()){
    //             return false;
    //         }
    //     }
    // }
}

int WaveFunctionCollapse::FindLowestEntropy(){
    // loop over all and Get entropy, remembering lowest
    float min_entropy = std::numeric_limits<float>::max();
    std::cout << "Finding lowest Entropy" << std::endl;
    wfc::Tile* lowest = nullptr;
    bool all_collapsed = true;
    // TODO can add class for world_ to make this and other things easier
    for(auto& row:world_){
        for(auto& tile:row){
            if (!tile.IsCollapsed()){
                all_collapsed = false;
                if (tile.GetEntropy() < min_entropy){
                    lowest = &tile;
                    min_entropy = tile.GetEntropy();
                }
            }
        }
    }
    if (lowest){
        lowest_tile_ = lowest;
        return 0;
    }
    else if(all_collapsed){
        return 1;
    }
    else{
        return 2;
    }
}

void WaveFunctionCollapse::Propagate(wfc::Tile* updated_tile){
    std::vector<std::vector<wfc::Tile*>> neighbours = updated_tile->GetNeighbours();
    for(auto row:neighbours){
        for(auto tile:row){
            tile->UpdateState();
        }
    }
}

std::vector<std::vector<int>> WaveFunctionCollapse::PrepareRenderWorld(){
    std::vector<std::vector<int>> int_world(width_, std::vector<int>(height_, 0));
    for(int y=0; y<height_; ++y){
        for(int x=0; x<width_; ++x){
            if(world_[x][y].IsCollapsed()){
                int_world[x][y] = world_[x][y].final_state_.value();
            }
            else{
                int_world[x][y] = num_states_ + 1;
            }
        }
    }
    for(auto row:int_world){
        for(auto num:row){
            std::cout << num;
        }
        std::cout << std::endl;
    }
    return int_world;
}

void WaveFunctionCollapse::AddRenderer(renderer::WorldRenderer* renderer){
    renderer_ = renderer;
}
} // namespace wfc