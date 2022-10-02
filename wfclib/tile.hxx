#ifndef WaveFC_wfclib_tile_HXX
#define WaveFC_wfclib_tile_HXX

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <optional>
#include <set>

#include "pattern.hxx"

namespace wfc
{

class Tile
{
private:
    bool collapsed_;
    float entropy_;
    float sum_weights_;
    int num_patterns_;
    std::vector<wfc::Pattern> patterns_;
    std::map<wfc::Pattern, float> state_;
    std::vector<Tile*> neighbours_;
    int GetRandomState();
    inline void UpdateSumWeights();
public:
    Tile(std::map<wfc::Pattern, int> pattern_distro);
    std::optional<wfc::Pattern> final_state_;
    int CollapseState();
    void UpdateEntropy();
    void UpdateState(std::map<int,int> impossible_states);
    void SetNeighbours(std::vector<Tile*> neighbours);
    std::vector<Tile*> GetNeighbours();
    float GetEntropy();
    bool IsCollapsed();
};

} // namespace wfc


#endif // WaveFC_wfclib_tile_HXX