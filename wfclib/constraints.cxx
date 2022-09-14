#include "constraints.hxx"
#include "tile.hxx"

#include <iostream>

namespace wfc {

Constraints::Constraints()
{
    // Constructor
    std::cout << "Making a Constraints object" << std::endl;
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
    return constrained_states;
}


} // namespace wfc