#ifndef WaveFC_wfclib_tile_HXX
#define WaveFC_wfclib_tile_HXX

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <optional>

namespace wfc
{

class Tile
{
private:
    int num_states_;
    bool collapsed_;
    float entropy_;
    float sum_weights_;
    std::unordered_map<int,int> state_distro_;
    std::unordered_map<int, float> state_;
    std::vector<std::vector<Tile*>> neighbours_;
    int GetRandomState();
    inline void UpdateSumWeights();
public:
    Tile(std::unordered_map<int,int> start_distro);
    std::optional<int> final_state_;
    int CollapseState();
    void UpdateEntropy();
    void UpdateState(std::unordered_map<int,float> constrained_states);
    void SetNeighbours(std::vector<std::vector<Tile*>> neighbours);
    std::vector<std::vector<Tile*>> GetNeighbours();
    float GetEntropy();
    bool IsCollapsed();
};

} // namespace wfc


#endif // WaveFC_wfclib_tile_HXX