#include "tile.hxx"
#include <math.h>

namespace wfc {

Tile::Tile(int num_states)//, Constraints* constraints)
{
    num_states_ = num_states;
    collapsed_ = false;
    final_state_ = std::nullopt;

    float uniform_weight = 1.0/num_states;
    for(int i=0; i< num_states_; ++i){
        state_[i] = uniform_weight;
    }
    sum_weights_ = uniform_weight*num_states;

    //constraints_ = constraints;
    this->UpdateEntropy();
}

Tile::~Tile()
{
    // Destructor
    //std::cout << "Destructing Tile" << std::endl;
}

void Tile::UpdateState(std::unordered_map<int,float> constrained_states){
    // Look at neigbours and update superposition
    // Look at neighbours.
    // Find patterns that still match
    // Find what tile each would make this tile
    // Sum counts and split probabilities.
    //TODO this is quick hacky test
    // if (neighbours_[0][0]){
    //     state_[0]*=0.5;
    // }
    // constrained states needs to be normalised
    // do we want to maintain that state_ always has entries for all state ids
    if (!collapsed_){
        // do the updating
        state_ = constrained_states;
        this->UpdateEntropy();
        this->UpdateSumWeights();
    }
    else{
        state_ = std::unordered_map<int,float>();
    }
}

void Tile::UpdateSumWeights(){
    sum_weights_ = 0;
    for (auto const& [id, prob] : state_){
        sum_weights_ += prob;
    }
    std::cout << "Sum weights (should be 1!)" << sum_weights_ << std::endl;
}

void Tile::UpdateEntropy(){
    // - sum (p(x)log(px))
    if(!collapsed_){
        entropy_ = 0;
        for (auto const& [id, prob] : state_){
            entropy_ -= (prob * std::log(prob));
        }
        std::cout << "Entropy Updated " << entropy_ << std::endl;
    }
}

float Tile::GetEntropy(){
    return entropy_;
}

void Tile::SetNeighbours(std::vector<std::vector<Tile*>> neighbours){
    neighbours_ = neighbours;
}

std::vector<std::vector<Tile*>> Tile::GetNeighbours(){
    return neighbours_;
}

int Tile::CollapseState(){
    // Collapse into a weighted random choice of state
    if (!state_.size()){
        std::cout << "Contradiction encountered" << std::endl;
        return -1;
    }
    int r_state =  this->GetRandomState();
    final_state_ = r_state;
    collapsed_ = true;
    entropy_ = 0;
    std::cout << "Collapsing to state " << r_state << std::endl;
    return r_state;
}

int Tile::GetRandomState(){
    // Picks a weighted random state
    // TODO change to make random between 0 and sum of states rather than 1
    // so we can avoid renormalizing after each updated.
    //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r = static_cast <float> (rand()) / (static_cast <float>(RAND_MAX) /sum_weights_);
    for(int i=0; i<num_states_; ++i) {
        if(r < state_[i])
            return i;
        r -= state_[i];
    }
    return -1;
}

bool Tile::IsCollapsed(){
    return collapsed_;
}


} // namespace wfc
