#include "tile.hxx"

namespace wfc {

Tile::Tile(int num_states, Constraints* constraints)
{
    num_states_ = num_states;
    collapsed_ = false;
    final_state_ = std::nullopt;

    float uniform_weight = 1.0/num_states;
    for(int i=0; i< num_states_; ++i){
        state_[i] = uniform_weight;
    }

    constraints_ = constraints;
}

Tile::~Tile()
{
    // Destructor
    std::cout << "Destructing Tile" << std::endl;
}

void Tile::UpdateState(){
    // Look at neigbours and update superposition
    // Look at neighbours.
    // Find patterns that still match
    // Find what tile each would make this tile
    // Sum counts and split probabilities.
}

void Tile::SetNeighbours(std::vector<std::vector<Tile*>> neighbours){
    neighbours_ = neighbours;
}

std::vector<std::vector<Tile*>> Tile::GetNeighbours(){
    return neighbours_;
}

int Tile::CollapseState(){
    // Collapse into a weighted random choice of state
    int r_state =  this->GetRandomState();
    final_state_ = r_state;
    std::cout << "Collapsing to state " << r_state << std::endl;
    return r_state;
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
