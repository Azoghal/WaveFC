#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints(){
    
}

Constraints::Constraints(std::map<int, std::vector<std::map<int,int>>> constraints){
    // Pattern ID to 4 directions worth of sets
    // Right Bottom Left Top
    constraints_ = constraints;
    std::vector<int> pattern_ids;
    for (auto& [id,count] : constraints_){
        pattern_ids.push_back(id);
    }
    unconstrained_ = this->BuildConstrainedSets(pattern_ids)[0];
}

std::map<int,int> Constraints::GetUnconstrained(){
    return unconstrained_;
}

std::vector<std::map<int,int>> Constraints::GetConstrainedSets(int pattern_id){
    // [0] contains a map of pattern ids and weight/count that are valid for a tile to the right to have
    // Tile Update state will then make any REDUCTIONS to counts in its state vector
    return constraints_[pattern_id];
    //return std::vector<std::map<int,int>>(4,std::map<int,int>());
}

std::vector<std::map<int,int>> Constraints::BuildConstrainedSets(std::vector<int> pattern_ids){
    // Composite by summing independent possibilities (as only one possible final result in each direction)
    std::vector<std::map<int,int>> total_constrained(4,std::map<int,int>());
    for (int pattern_id : pattern_ids){
        for (int i=0; i<4; ++i){
            for (auto& [inner_id ,count] : constraints_[pattern_id][i]){
                total_constrained[i][inner_id] += count;
            }
        }
    }
    
    return total_constrained;
}

} // namespace wfc