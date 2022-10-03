#include "tile.hxx"
#include <math.h>


namespace wfc {

Tile::Tile(std::map<int,int> unconstrained_state, std::map<int,wfc::Pattern> patterns)//, Constraints* constraints)
{
    // Find the number of used states, and total for normalising
    num_patterns_ = unconstrained_state.size();

    patterns_ = patterns;
    std::cout << "Patterns that are tracked:" << std::endl;
    for (auto& [p_id, pattern] : patterns){
        std::cout << p_id << std::endl;
    }

    sum_weights_ = 0;
    for (auto& [p_id, count] : unconstrained_state){
        sum_weights_ += count;
        state_[p_id] = count;
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
        std::cout << "  Old | New" << std::endl;
        //for (auto& [p_id, current_weight] : state_){
        for (int p_id=1; p_id< num_patterns_+1; ++p_id){
            int current_weight = state_[p_id];
            int new_weight = constrained_states[p_id];
            std::cout << p_id << ":  " << current_weight << "   ";
            if (new_weight < current_weight){
                state_[p_id] = new_weight;
            }
            std::cout << new_weight << std::endl;
        }
        std::cout << "Total" << std::endl;
        for (auto& [key,val] : state_){
            std::cout << key << ":  " << val << "   " << std::endl << std::endl;
        }
        std::cout << "New Entropy" << entropy_ << std::endl;
        this->UpdateSumWeights();
        this->UpdateEntropy();
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
            if (prob > 0){
                entropy_ -= (prob * std::log(prob));
            }
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
    for(auto& [id, weight]: state_) {
        if(r < weight)
            return id;
        r -= weight;
    }
    return -1;
}

bool Tile::IsCollapsed(){
    return collapsed_;
}


} // namespace wfc
