#include "wave_function_collapse.hxx"
#include <limits>
#include <stdlib.h>

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(int p_width, int p_height, int tile_size, Constraints constraints, std::map<wfc::Pattern,int> pattern_distro)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
    p_width_ = p_width;
    p_height_ = p_height;
    t_width_ = p_width/tile_size;
    t_height_ = p_height/tile_size;
    tile_size_ = tile_size;
    constraints_ = constraints;
    pattern_distro_ = pattern_distro;
    this->SetupTiles();
    lowest_tile_ = nullptr;
    renderer_ = nullptr;
}

void WaveFunctionCollapse::SetupTiles(){
    world_ = std::vector<std::vector<Tile>>(t_width_, std::vector<Tile>(t_height_, Tile(pattern_distro_)));
    // set neighbours of tiles
    // calculate all their entropies and store minimum
    // options: loop neighbours around
    // setup fake neighbours
    for(int y=0; y<t_height_; ++y){
        for(int x=0; x<t_width_; ++x){
            std::vector<std::vector<Tile*>> neighbours(3,std::vector<Tile*>(3,nullptr));
            for (int j=-1; j<2; ++j){
                for (int i=-1; i<2; ++i){
                    int xx = (x + i + t_width_) % t_width_;
                    int yy = (y + j + t_height_) % t_height_;
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
            std::map<wfc::Pattern,float> constrained_states = constraints_.GetConstrainedStates(*tile);
            tile->UpdateState(constrained_states);
        }
    }
}

std::vector<std::vector<int>> WaveFunctionCollapse::PrepareRenderWorld(){
    std::vector<std::vector<int>> int_world(p_width_, std::vector<int>(p_height_, -1));
    // Change this to getting subgrid from pattern
    for(int j=0; j<t_height_; ++j){
        for(int i=0; i<t_width_; ++i){
            if(world_[i][j].IsCollapsed()){
                for (int y=0; y<p_height_; ++y){
                    for (int x=0; x<p_width_; ++x){
                        int yy = y + j*tile_size_;
                        int xx = x + i*tile_size_;
                        wfc::Pattern p = world_[i][j].final_state_.value();
                        int_world[xx][yy] = p.GetPattern()[i][j];
                    }
                }
            }
        }
    }
    return int_world;
}

void WaveFunctionCollapse::AddRenderer(renderer::WorldRenderer* renderer){
    renderer_ = renderer;
}
} // namespace wfc