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
}

std::vector<std::map<int,int>> Constraints::GetConstrainedSets(int pattern_id){
    //return constraints_[pattern_id];
    return std::vector<std::map<int,int>>(4,std::map<int,int>());
}

std::vector<std::map<int,int>> Constraints::BuildConstrainedSets(std::vector<int> pattern_ids){
    for (int pattern_id : pattern_ids){

    }
    //return constraints_[pattern_ids[0]];
    return std::vector<std::map<int,int>>(4,std::map<int,int>());
}

} // namespace wfc