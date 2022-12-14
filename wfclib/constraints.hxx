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
    std::map<int,int> unconstrained_;
public:
    Constraints();
    Constraints(std::map<int, std::vector<std::map<int,int>>> constraints);
    std::map<int,int> GetUnconstrained();
    std::vector<std::map<int,int>> GetConstrainedSets(int pattern_id);
    std::vector<std::map<int,int>> BuildConstrainedSets(std::vector<int> pattern_ids);
    std::map<int, std::vector<std::map<int,int>>> GetConstraints();
    void Print();
};

} // namespace wfc

#endif // WaveFC_wfclib_constraints_HXX