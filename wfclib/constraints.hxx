#ifndef WaveFC_wfclib_constraints_HXX
#define WaveFC_wfclib_constraints_HXX

#include "pattern.hxx"
#include <map>
#include <vector>

namespace wfc{

class Constraints
{
private:
    /* data */
    std::map<wfc::Pattern, int> patterns_;
public:
    Constraints();
    ~Constraints();
    //std::map<int, int> FindValidOptions(wfc::Tile tile);
};

} // namespace wfc

#endif // WaveFC_wfclib_constraints_HXX