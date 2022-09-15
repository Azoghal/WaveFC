#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints()
{

}

Constraints::Constraints(std::map<wfc::Pattern, int> patterns)
{
    // Constructor
    patterns_ = patterns;
}

Constraints::~Constraints()
{
    // Destructor
}

std::map<int, int> Constraints::GetConstrainedStates(wfc::Tile tile){
    std::map<int, int> constrained_states;
    // Find states of any collapsed neighbours
    std::vector<std::vector<int>> neighbour_states;
    for (auto row : tile.GetNeighbours()){
        for (auto tile_p : row){
            if (tile_p->IsCollapsed()){
                std::cout << tile_p->final_state_.value();
            }
            else{
                std::cout << -1;
            }
        }
        std::cout << std::endl;
    }
    // Find all observed patterns that match
    std::cout << "about to do some iterations" << std::endl;
    for (auto const& [pattern, count] : patterns_){
        std::cout << "an iteration" << std::endl;
    }
    return constrained_states;
}


} // namespace wfc