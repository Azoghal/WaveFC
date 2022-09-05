#ifndef WaveFC_wfclib_tile_HXX
#define WaveFC_wfclib_tile_HXX

#include <unordered_map>
#include <vector>
#include <optional>

namespace wfc
{

class Tile
{
private:
    bool collapsed_;
    std::optional<int> final_state_;
    std::unordered_map<int, float> state_;
    std::vector<std::vector<Tile*>> neighbours_;
public:
    Tile(/* args */);
    ~Tile();
    void UpdateState();
    int CollapseState();
};

} // namespace wfc


#endif // WaveFC_wfclib_tile_HXX