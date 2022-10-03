#ifndef WaveFC_wfclib_pattern_HXX
#define WaveFC_wfclib_pattern_HXX

#include <vector>

namespace wfc{ 

class Pattern
{
private:
    int size_;
    int id_;
    std::vector<std::vector<int>> pattern_;
public:
    Pattern();
    Pattern(int id, int size);
    Pattern(int id, std::vector<std::vector<int>> pattern);
    std::vector<Pattern> GenerateRotations();
    std::vector<Pattern> GenerateReflections();
    std::vector<std::vector<int>> GetPattern();
    int GetPatternID() const;
    const bool operator<(Pattern const& rhs) const;
};

} // namespace wfc

#endif // WaveFC_wfclib_pattern_HXX
