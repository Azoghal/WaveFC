#include "wave_function_collapse.hxx"

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(std::vector<char> states, Constraints constraints, int width, int height)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
    width_ = width;
    height_ = height;
    constraints_ = constraints;
    this->SetupTiles();
}

WaveFunctionCollapse::~WaveFunctionCollapse()
{
    // destructor
}

void WaveFunctionCollapse::SetupTiles(){
    std::vector<std::vector<Tile>> world_(height_, std::vector<Tile>(width_, Tile(3, &constraints_)));

}


void WaveFunctionCollapse::CollapseOnce(){
    wfc::Tile* t = this->FindLowestEntropy();
    t->CollapseState();
    this->Propagate(t); // somehow needs to know 

}
void WaveFunctionCollapse::Collapse(){
    // Change condition
    while(true){
        this->CollapseOnce();
    }
}

wfc::Tile* WaveFunctionCollapse::FindLowestEntropy(){
    // loop over all and calculate entropy, remembering lowest
    // Speedup is to store an entropy for each of them,
    // only updating a few at a time as needed, and keeping track
    // of minimum
}

void WaveFunctionCollapse::Propagate(wfc::Tile* updated_tile){
    std::vector<std::vector<wfc::Tile*>> affected_tiles = updated_tile->GetNeighbours();
}
} // namespace wfc