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
    int t_width_, t_height_;
    int p_width_, p_height_;
    int tile_size_;
    int num_states_; // TODO check if needed
    std::vector<std::vector<Tile>> world_;
    Tile* lowest_tile_;
    Constraints constraints_;
    std::map<int,wfc::Pattern> patterns_;
    renderer::WorldRenderer* renderer_;
    void SetupTiles();
    int FindLowestEntropy();
    void Propagate(wfc::Tile* updated_tile);
    std::vector<std::vector<int>> PrepareRenderWorld();
public:
    WaveFunctionCollapse(int width, int height, int tile_size, wfc::Constraints constraints, std::map<int,wfc::Pattern> pattern);
    int CollapseOnce();
    int Collapse(bool wait_for_input);
    void AddRenderer(renderer::WorldRenderer* renderer);
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX