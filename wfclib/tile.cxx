#include "tile.hxx"
#include <math.h>

namespace wfc {

Tile::Tile(std::map<int,int> state_distro_)//, Constraints* constraints)
{
    num_states_ = state_distro_.size();
    float normaliser;
    for (auto& [id, count] : state_distro_){
        normaliser += count;
    }

    collapsed_ = false;
    final_state_ = std::nullopt;

    sum_weights_ = 0;
    for (auto& [id, count] : state_distro_){
        state_[id] = count/normaliser;
        sum_weights_ += count/normaliser;
    }

    if (sum_weights_ != 1){
        std::cout << "Sum Weights not 1" << std::endl;
    }
    //constraints_ = constraints;
    this->UpdateEntropy();
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
