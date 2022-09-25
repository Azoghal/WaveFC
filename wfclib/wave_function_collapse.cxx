#include "wave_function_collapse.hxx"
#include <limits>
#include <stdlib.h>

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(int width, int height, Constraints constraints)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
    width_ = width;
    height_ = height;
    constraints_ = constraints;
    this->SetupTiles();
    lowest_tile_ = nullptr;
    renderer_ = nullptr;
}

void WaveFunctionCollapse::SetupTiles(){
    world_ = std::vector<std::vector<Tile>>(width_, std::vector<Tile>(height_, Tile(state_distro_)));
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
        case 0: {
            std::cout << "Lowest Entropy" << lowest_tile_->GetEntropy() << std::endl;
            int collapsed_to = lowest_tile_->CollapseState();
            if (collapsed_to == -1){
                std::cout << "Contradiction reached" << std::endl;
                return 2;
            }
            this->Propagate(lowest_tile_);
            return 0;
        }
        case 1: {
            std::cout << "All tiles are collapsed" << std::endl;
            return 1;
        }
        case 2: {
            std::cout << "Contradiction reached" << std::endl;
            return 2;
        }
        default: {
            std::cout << "Unexepcted return code from FindLowestEntropy()" << std::endl;
            return 3;
        }
    }
}

int WaveFunctionCollapse::Collapse(bool wait_for_input){
    int result = 0;
    std::vector<std::vector<int>> int_world;
    while(result == 0){
        if (renderer_){
            int_world = this->PrepareRenderWorld();
            renderer_->SetWorld(int_world);
            renderer_->PrintWorld();
            if (wait_for_input) {
                std::cin.ignore();
            }
        }
        result = this->CollapseOnce();
    }
    if (result == 1){
        // successful, no error
        return 0;
    }
    else{
        // Contradiction or error
        return 1;
    }
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
                float entropy = tile.GetEntropy();
                if (entropy < min_entropy){
                    lowest = &tile;
                    min_entropy = entropy;
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
        // Contradiction as not all collapsed
        // This case should not occur, contradictions are checked 
        // at collapse time.
        return 2;
    }
}

void WaveFunctionCollapse::Propagate(wfc::Tile* updated_tile){
    // Find neighbours that need updated superposition
    std::cout << "Propogating changes" << std::endl;
    std::vector<std::vector<wfc::Tile*>> neighbours = updated_tile->GetNeighbours();
    for(auto row:neighbours){
        for(auto tile:row){
            std::unordered_map<int,float> constrained_states = constraints_.GetConstrainedStates(*tile);
            tile->UpdateState(constrained_states);
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
                int_world[x][y] = -1;
            }
        }
    }
    return int_world;
}

void WaveFunctionCollapse::AddRenderer(renderer::WorldRenderer* renderer){
    renderer_ = renderer;
}
} // namespace wfc