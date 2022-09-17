#ifndef WaveFC_wfclib_wave_function_collapse_HXX
#define WaveFC_wfclib_wave_function_collapse_HXX

#include <vector>
#include <iostream>
#include <unordered_map>

#include "world_renderer.hxx"
#include "constraints.hxx"
#include "tile.hxx"


namespace wfc{

class WaveFunctionCollapse
{
private:
    int width_, height_;
    int num_states_; // TODO check if needed
    std::vector<std::vector<Tile>> world_;
    Tile* lowest_tile_;
    Constraints constraints_;
    std::unordered_map<int,int> state_distro_;
    renderer::WorldRenderer* renderer_;
    void SetupTiles();
    int FindLowestEntropy();
    void Propagate(wfc::Tile* updated_tile);
    std::vector<std::vector<int>> PrepareRenderWorld();
public:
    WaveFunctionCollapse(int width, int height, wfc::Constraints constraints, std::unordered_map<int,int> state_distro);
    int CollapseOnce();
    int Collapse(bool wait_for_input);
    void AddRenderer(renderer::WorldRenderer* renderer);
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX