#ifndef WaveFC_wfclib_wave_function_collapse_HXX
#define WaveFC_wfclib_wave_function_collapse_HXX

#include <vector>
#include <iostream>
#include <map>

#include "world_renderer.hxx"

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
    std::map<int, char> state_characters_;
    renderer::WorldRenderer* renderer_;
    int num_states_;
    void SetupTiles();
    int FindLowestEntropy();
    void Propagate(wfc::Tile* updated_tile);
    std::vector<std::vector<int>> PrepareRenderWorld();
public:
    WaveFunctionCollapse(int width, int height, int num_states, wfc::Constraints constraints);
    ~WaveFunctionCollapse();
    int CollapseOnce();
    int Collapse();
    void AddRenderer(renderer::WorldRenderer* renderer);
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX