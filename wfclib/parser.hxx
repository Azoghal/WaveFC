#ifndef WaveFC_wfclib_parser_HXX
#define WaveFC_wfclib_parser_HXX

#include <vector> 
#include <map>
#include "constraints.hxx"
#include "pattern.hxx"


namespace wfc{

class Parser
{
private:
    int kernel_size_;
    std::vector<std::vector<int>> input_;
    void CheckKernelSize();
    std::map<wfc::Pattern, int> GetKernelPatterns();
public:
    Parser(std::vector<std::vector<int>> input, int kernel_size);
    ~Parser();
    void SetKernelSize(int kernel_size);
    void UpdateInput(std::vector<std::vector<int>> new_input);
    wfc::Constraints Parse();
};


} // namespace wfc

#endif //WaveFC_wfclib_parser_HXX