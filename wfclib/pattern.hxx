#ifndef WaveFC_wfclib_pattern_HXX
#define WaveFC_wfclib_pattern_HXX

#include <vector>

namespace wfc{ 

class Pattern
{
private:
    int size_;
    std::vector<std::vector<int>> pattern_;
public:
    Pattern(int size);
    Pattern(std::vector<std::vector<int>> pattern);
    std::vector<Pattern> GenerateRotations();
    std::vector<Pattern> GenerateReflections();
    bool CheckMatches(std::vector<std::vector<int>> to_compare_) const;
    const bool operator<(Pattern const& rhs) const;
    int GetCentre() const;
};

} // namespace wfc

#endif // WaveFC_wfclib_pattern_HXX
