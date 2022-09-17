#include "tile.hxx"
#include <math.h>

namespace wfc {

Tile::Tile(std::unordered_map<int,int> state_distro_)//, Constraints* constraints)
{
    // Find the number of used states, and total for normalising
    num_states_ = state_distro_.size();
    float normaliser;
    for (auto& [id, count] : state_distro_){
        normaliser += count;
    }

    // Starts uncollapsed and with no final state
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
    // Update state with newly constrained states.
    // TODO currently not correct, constraining strictly to one kernel when it actually lives in multiple.
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
    // TODO add assertion for sum_weights should be 1"
}

void Tile::UpdateEntropy(){
    // - sum (p(x)log(px))
    if(!collapsed_){
        entropy_ = 0;
        for (auto const& [id, prob] : state_){
            entropy_ -= (prob * std::log(prob));
        }
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
