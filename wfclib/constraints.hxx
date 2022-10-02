#ifndef WaveFC_wfclib_constraints_HXX
#define WaveFC_wfclib_constraints_HXX

#include "pattern.hxx"
#include "tile.hxx"
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

namespace wfc{

class Constraints
{
private:
    std::map<int, std::vector<std::map<int,int>>> constraints_;
public:
    Constraints();
    Constraints(std::map<int, std::vector<std::map<int,int>>> constraints);
    std::vector<std::set<int>> GetConstrainedSets(int pattern_id);
    std::vector<std::set<int>> BuildConstrainedSets(std::set<int> pattern_ids);
};

} // namespace wfc

#endif // WaveFC_wfclib_constraints_HXX