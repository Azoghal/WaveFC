#include "tile.hxx"

namespace wfc {

Tile::Tile(int num_states)
{
    num_states_ = num_states;
    collapsed_ = false;
    final_state_ = std::nullopt;
    float uniform_weight = 1.0/num_states;
    for(int i=0; i< num_states_; ++i){
        state_[i] = uniform_weight;
    }
}

Tile::~Tile()
{
    // Destructor
    std::cout << "Destructing Tile" << std::endl;
}

void Tile::UpdateState(){
    // Look at neigbours and update superposition
}

int Tile::CollapseState(){
    // Collapse into a weighted random choice of state
    std::cout << this->GetRandomState() << std::endl;
    return 0;
}

int Tile::GetRandomState(){
    // Picks a weighted random state
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    for(int i=0; i<num_states_; ++i) {
        if(r < state_[i])
            return i;
        r -= state_[i];
    }
    return -1;
}




} // namespace wfc
