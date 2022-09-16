#ifndef WaveFC_wfclib_parser_HXX
#define WaveFC_wfclib_parser_HXX

#include <vector> 
#include <unordered_map>
#include "constraints.hxx"
#include "pattern.hxx"


namespace wfc{

class Parser
{
private:
    int kernel_size_;
    std::vector<std::vector<int>> input_;
    void CheckKernelSize();
    std::pair<std::unordered_map<int,int>, std::map<wfc::Pattern, int>> ParseLoop();
    std::unordered_map<int,int> state_distribution_;
    wfc::Constraints constraints_;
public:
    Parser(std::vector<std::vector<int>> input, int kernel_size);
    void SetKernelSize(int kernel_size);
    void UpdateInput(std::vector<std::vector<int>> new_input);
    void Parse();
    wfc::Constraints GetConstraints();
    std::unordered_map<int,int> GetStateDistribution();
};


} // namespace wfc

#endif //WaveFC_wfclib_parser_HXX