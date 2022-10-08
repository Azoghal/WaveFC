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
    std::map<int, wfc::Pattern> patterns_;
    std::map<std::vector<std::vector<int>>, int> pattern_ids_;
    int next_pattern_id_;
    std::vector<std::vector<int>> ReadInput(std::string filename);
    std::pair<int,std::string> ReadToken(std::string line);
    std::vector<std::string> TokeniseLine(std::string line);
    int InputCharToInt(std::string s);
    int InputCharToInt(char c);
    int GeneratePatternID(std::vector<std::vector<int>> pattern);
    void CheckKernelSize();
    void ParseLoop();
public:
    Parser();
    void SetKernelSize(int kernel_size);
    void UpdateInput(std::vector<std::vector<int>> new_input);
    void Parse(std::string input_file, int kernel_size);
    void Parse(std::string input_file, int kernel_size, bool save);
    void SaveParse(std::string output_file);
    void LoadParse(std::string input_file);
    wfc::Constraints GetConstraints();
    std::map<int,wfc::Pattern> GetPatterns();
    int GetKernelSize();
};


} // namespace wfc

#endif //WaveFC_wfclib_parser_HXX