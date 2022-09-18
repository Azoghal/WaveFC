#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints(std::map<wfc::Pattern, int> patterns)
{
    patterns_ = patterns;
}

Constraints::Constraints()
{
    // Default constructor for parser and wfc initialisation
    Constraints(std::map<wfc::Pattern, int>());
}

std::unordered_map<int, float> Constraints::GetConstrainedStates(wfc::Tile tile){
    std::unordered_map<int, float> constrained_states;
    // Find states of any collapsed neighbours
    std::vector<std::vector<int>> neighbour_states;
    for (auto row : tile.GetNeighbours()){
        std::vector<int> int_row;
        for (auto tile_p : row){
            if (tile_p->IsCollapsed()){
                int_row.push_back(tile_p->final_state_.value());
            }
            else{
                int_row.push_back(-1);
            }
        }
        neighbour_states.push_back(int_row);
    }

    // Find all observed patterns that match
    float total_count = 0;
    for (auto const& [pattern, count] : patterns_){
        if (pattern.CheckMatches(neighbour_states)){
            int centre_state= pattern.GetCentre();
            constrained_states[centre_state] += count;
            total_count += count;
        }
    }
    
    // Normalise
    for (auto const& [pattern, weight] : constrained_states){
        constrained_states[pattern] = weight / total_count;
    }
    return constrained_states;
}


} // namespace wfc