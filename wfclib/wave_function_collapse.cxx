#include "wave_function_collapse.hxx"

namespace wfc {
    
WaveFunctionCollapse::WaveFunctionCollapse(char states[], std::vector<wfc::Constraint>)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
}

WaveFunctionCollapse::~WaveFunctionCollapse()
{
    // destructor
}

} // namespace wfc