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
    std::vector<std::vector<Tile>> world_;
    int width_, height_;
    Constraints constraints_;
    Tile* lowest_tile_;
    std::unordered_map<int, char> state_characters_;
    renderer::WorldRenderer* renderer_;
    int num_states_;
    std::map<int,int> state_distro_;
    void SetupTiles();
    int FindLowestEntropy();
    void Propagate(wfc::Tile* updated_tile);
    std::vector<std::vector<int>> PrepareRenderWorld();
public:
    WaveFunctionCollapse(int width, int height, wfc::Constraints constraints, std::map<int,int> state_distro);
    ~WaveFunctionCollapse();
    int CollapseOnce();
    int Collapse(bool wait_for_input);
    void AddRenderer(renderer::WorldRenderer* renderer);
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX