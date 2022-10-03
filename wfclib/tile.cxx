#include "tile.hxx"
#include <math.h>


namespace wfc {

Tile::Tile(std::map<wfc::Pattern,int> pattern_distro)//, Constraints* constraints)
{
    // Find the number of used states, and total for normalising
    num_patterns_ = pattern_distro.size();
    patterns_ = std::map<int, wfc::Pattern>();

    //float normaliser;
    sum_weights_ = 0;
    for (auto& [pattern, count] : pattern_distro){
        sum_weights_ += count;
        patterns_[pattern.GetPatternID()] = pattern;
        state_[pattern.GetPatternID()] = count;
    }

    // Starts uncollapsed and with no final state
    collapsed_ = false;
    final_state_ = std::nullopt;

    this->UpdateEntropy();
}

void Tile::UpdateState(std::map<int,int> constrained_states){
    // Remove the given count from each part of the state.
    // Change to boolean if anything changed - determines if children added to queue.
    if (!collapsed_){
        // do the updating
        //state_ = constrained_states;
        this->UpdateEntropy();
        this->UpdateSumWeights();
    }
    else{
        state_ = std::map<int,float>();
    }
}

void Tile::UpdateSumWeights(){
    sum_weights_ = 0;
    for (auto const& [pattern, weight] : state_){
        sum_weights_ += weight;
    }
}

void Tile::UpdateEntropy(){
    // - sum (p(x)log(px))
    if(!collapsed_){
        entropy_ = 0;
        for (auto const& [pattern, weight] : state_){
            float prob = weight / sum_weights_;
            entropy_ -= (prob * std::log(prob));
        }
    }
}

float Tile::GetEntropy(){
    return entropy_;
}

void Tile::SetNeighbours(std::vector<Tile*> neighbours){
    neighbours_ = neighbours;
}

std::vector<Tile*> Tile::GetNeighbours(){
    return neighbours_;
}

int Tile::CollapseState(){
    // Collapse into a weighted random choice of state
    if (!state_.size()){
        std::cout << "Contradiction encountered" << std::endl;
        return -1;
    }
    int r_state =  this->GetRandomState();
    std::cout << "random index: " << r_state << std::endl;
    final_state_ = patterns_[r_state];
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
    std::cout << "Sum_weights: " << sum_weights_ << std::endl;
    for(auto& [id, weight]: state_) {
        std::cout << "R: " << r << std::endl;
        std::cout << id << " " << weight << std::endl;
        if(r < weight)
            return id;
        r -= weight;
    }
    std::cout << "Random broken" << std::endl;
    return -1;
}

bool Tile::IsCollapsed(){
    return collapsed_;
}


} // namespace wfc
