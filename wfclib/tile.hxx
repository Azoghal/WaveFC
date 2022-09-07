#ifndef WaveFC_wfclib_tile_HXX
#define WaveFC_wfclib_tile_HXX

#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>

#include "constraints.hxx"

namespace wfc
{

class Tile
{
private:
    int num_states_;
    bool collapsed_;
    float entropy_;
    std::optional<int> final_state_;
    std::unordered_map<int, float> state_;
    std::vector<std::vector<Tile*>> neighbours_;
    Constraints* constraints_;
    int GetRandomState();
public:
    Tile(int num_states, Constraints* constraints);
    ~Tile();
    void UpdateState();
    void SetNeighbours(std::vector<std::vector<Tile*>> neighbours);
    std::vector<std::vector<Tile*>> GetNeighbours();
    int CollapseState();
    void UpdateEntropy();
    float GetEntropy();
    bool IsCollapsed();
};

} // namespace wfc


#endif // WaveFC_wfclib_tile_HXX