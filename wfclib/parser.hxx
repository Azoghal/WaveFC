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
    std::unordered_map<int,int> state_distribution_;
    wfc::Constraints constraints_;
    void CheckKernelSize();
    int InputCharToInt(char c);
    std::pair<std::unordered_map<int,int>, std::map<wfc::Pattern, int>> ParseLoop();

public:
    Parser(std::string input_file, int kernel_size);
    void SetKernelSize(int kernel_size);
    void UpdateInput(std::vector<std::vector<int>> new_input);
    void Parse();
    std::vector<std::vector<int>> ReadInput(std::string filename);
    wfc::Constraints GetConstraints();
    std::unordered_map<int,int> GetStateDistribution();
};


} // namespace wfc

#endif //WaveFC_wfclib_parser_HXX