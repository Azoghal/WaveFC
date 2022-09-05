#ifndef WaveFC_wfclib_wave_function_collapse_HXX
#define WaveFC_wfclib_wave_function_collapse_HXX

#include <vector>
#include <iostream>

#include "constraint.hxx"
#include "tile.hxx"

namespace wfc{

class WaveFunctionCollapse
{
private:
    /* data */
public:
    WaveFunctionCollapse(char states[], std::vector<wfc::Constraint> constraints);
    ~WaveFunctionCollapse();
};

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX