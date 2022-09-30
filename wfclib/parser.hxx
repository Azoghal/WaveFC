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
    wfc::Constraints constraints_;
    std::map<wfc::Pattern, int> pattern_distro_;
    std::map<wfc::Pattern, int> pattern_ids_;
    int next_pattern_id_;
    void CheckKernelSize();
    int InputCharToInt(char c);
    void ParseLoop();
    int GetPatternID(wfc::Pattern pattern);

public:
    Parser(std::string input_file, int kernel_size);
    void SetKernelSize(int kernel_size);
    void UpdateInput(std::vector<std::vector<int>> new_input);
    void Parse();
    std::vector<std::vector<int>> ReadInput(std::string filename);
    wfc::Constraints GetConstraints();
    std::map<wfc::Pattern, int> GetPatternDistro();
};


} // namespace wfc

#endif //WaveFC_wfclib_parser_HXX