#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints(std::map<wfc::Pattern, int> patterns)
{
    patterns_ = patterns;
    // Encode this appears to left of... right of... etc.
}

Constraints::Constraints()
{
    // Default constructor for parser and wfc initialisation
    Constraints(std::map<wfc::Pattern, int>());
}

std::map<wfc::Pattern, float> Constraints::GetConstrainedStates(wfc::Tile tile){
    std::map<wfc::Pattern, float> constrained_states;
    // Find states of any collapsed neighbours
    std::vector<std::vector<std::optional<wfc::Pattern>>> neighbour_states;
    for (auto row : tile.GetNeighbours()){
        std::vector<std::optional<wfc::Pattern>> pattern_row;
        for (auto tile_p : row){
            pattern_row.push_back(tile_p->final_state_);
        }
        neighbour_states.push_back(pattern_row);
    }

    // Find all observed patterns that match
    // float total_count = 0;
    // for (auto const& [pattern, count] : patterns_){
    //     if (pattern.CheckMatches(neighbour_states)){
    //         constrained_states[centre_state] += count;
    //         total_count += count;
    //     }
    // }
    
    // Normalise
    // for (auto const& [pattern, weight] : constrained_states){
    //     constrained_states[pattern] = weight / total_count;
    // }

    // Placeholder
    for (auto const& [pattern, count] : patterns_){
            constrained_states[pattern] = count;
    }
    return constrained_states;
}


} // namespace wfc