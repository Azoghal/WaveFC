#include "wave_function_collapse.hxx"
#include <limits>

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(std::vector<char> states, Constraints constraints, int width, int height)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
    width_ = width;
    height_ = height;
    constraints_ = constraints;
    this->SetupTiles();
    lowest_tile_ = nullptr;
}

WaveFunctionCollapse::~WaveFunctionCollapse()
{
    // destructor
}

void WaveFunctionCollapse::SetupTiles(){
    world_ = std::vector<std::vector<Tile>>(height_, std::vector<Tile>(width_, Tile(height_, &constraints_)));
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

bool WaveFunctionCollapse::Collapse(){
    int result = 0;
    while(result == 0){
        std::cout << "Make call to rendlib here" << std::endl;
        result = this->CollapseOnce();
    }
    if (result == 1){
        return true;
    }
    else{
        return false;
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
            tile->UpdateEntropy();
        }
    }
}
} // namespace wfc