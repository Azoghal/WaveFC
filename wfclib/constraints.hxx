#ifndef WaveFC_wfclib_constraints_HXX
#define WaveFC_wfclib_constraints_HXX

#include "pattern.hxx"
#include "tile.hxx"
#include <unordered_map>
#include <map>
#include <vector>

namespace wfc{

class Constraints
{
private:
    std::map<wfc::Pattern, int> patterns_;
public:
    Constraints();
    Constraints(std::map<wfc::Pattern, int> patterns);
    std::unordered_map<int, float> GetConstrainedStates(wfc::Tile tile);
};

} // namespace wfc

#endif // WaveFC_wfclib_constraints_HXX