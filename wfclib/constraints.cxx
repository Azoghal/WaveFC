#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints(){
    
}

Constraints::Constraints(std::map<int, std::vector<std::set<int>>> constraints){
    // Pattern ID to 4 directions worth of sets
    // Right Bottom Left Top
    constraints_ = constraints;
}

std::vector<std::set<int>> Constraints::GetConstrainedSets(int pattern_id){
    return std::vector<std::set<int>>();
}

std::vector<std::set<int>> Constraints::BuildConstrainedSets(std::set<int> pattern_ids){
    return std::vector<std::set<int>>();
}

} // namespace wfc