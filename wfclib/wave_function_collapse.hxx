#ifndef WaveFC_wfclib_wave_function_collapse_HXX
#define WaveFC_wfclib_wave_function_collapse_HXX

#include <vector>
#include <iostream>

#include "constraints.hxx"
#include "tile.hxx"

namespace wfc{

class WaveFunctionCollapse
{
private:
    std::vector<std::vector<Tile>> world_;
    int width_, height_;
    Constraints constraints_;
    Tile* lowest_tile_;
    void SetupTiles();
    int FindLowestEntropy();
    void Propagate(wfc::Tile* udpated_tile);
public:
    WaveFunctionCollapse(std::vector<char> states, wfc::Constraints constraints, int width, int height);
    ~WaveFunctionCollapse();
    int CollapseOnce();
    bool Collapse();
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX