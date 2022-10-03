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
    std::cout << "WaveFunction collapse of " << t_width_ << "x" << t_height_ << " tiles, ";
    std::cout << "of size " << tile_size << "x" << tile_size << " pixels, ";
    std::cout << "giving a canvas size of " << p_width_ << "x" << p_height_ << std::endl;
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
            //std::vector<std::vector<Tile*>> neighbours(3,std::vector<Tile*>(3,nullptr));
            std::vector<Tile*> neighbours;
            int left = (x - 1 + t_width_) % t_width_;
            int right = (x + 1 + t_width_) % t_width_;
            int top = (y - 1 + t_height_) % t_height_;
            int bottom = (y + 1 + t_height_) % t_height_;
            // for (int j=-1; j<2; ++j){
            //     for (int i=-1; i<2; ++i){
            //         int xx = (x + i + t_width_) % t_width_;
            //         int yy = (y + j + t_height_) % t_height_;
            //         neighbours[i+1][j+1] = &world_[xx][yy];
            //     }
            // }
            neighbours.push_back(&world_[right][y]);
            neighbours.push_back(&world_[x][top]);
            neighbours.push_back(&world_[left][y]);
            neighbours.push_back(&world_[x][bottom]);
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
    std::vector<wfc::Tile*> neighbours = updated_tile->GetNeighbours();
    // Add neighbours of changed tile to queue.
    // Loop while queue not empty:
    //     Pop tile
    //     Get neighbours
    //     Calculate if set must be reduced
    //          reduce set
    //          add neighbours to queue
    // Do queue based bfs propagations
    std::vector<int> pattern_ids;
    pattern_ids.push_back(updated_tile->final_state_.value().GetPatternID());
    std::vector<std::map<int,int>> constrained_states = constraints_.BuildConstrainedSets(pattern_ids);
    for (int i=0; i < 4; ++i){
        wfc::Tile* neighbour = neighbours[i];
        std::map<int,int> constrained_direction = constrained_states[i];
        neighbour->UpdateState(constrained_direction);
        // Inform the neighbours of thze count of states that are no longer 
        // viable because of the newly updated tile.
        // If newly updated is A
        // and we look to the right, originally could have been A(4) or B(4)
        // then we inform it to subtract B(4) from the state
        // If newly updated is A or B
        // And originally right of could have been A(4) B(4) C(4)
        // Then we inform it to subtract C(4) and D
        // If overall state started as A(16) B(16) C(16) D(16) for example
        // We end up with A(16) B(16) C(12)
    }
    for(auto tile:neighbours){
        //std::map<wfc::Pattern,float> constrained_states = constraints_.GetConstrainedStates(*tile);
        //tile->UpdateState(constrained_states);
    }
}

std::vector<std::vector<int>> WaveFunctionCollapse::PrepareRenderWorld(){
    std::vector<std::vector<int>> int_world(p_width_, std::vector<int>(p_height_, -1));
    for(int j=0; j<t_height_; ++j){
        for(int i=0; i<t_width_; ++i){
            if(world_[i][j].IsCollapsed()){
                wfc::Pattern p = world_[i][j].final_state_.value();
                std::vector<std::vector<int>> int_pattern = p.GetPattern();
                for (int y=0; y<tile_size_; ++y){
                    for (int x=0; x<tile_size_; ++x){
                        int yy = y + j*tile_size_;
                        int xx = x + i*tile_size_;
                        int_world[xx][yy] = int_pattern[x][y];
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