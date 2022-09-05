#ifndef WaveFC_wfclib_wave_function_collapse_HXX
#define WaveFC_wfclib_wave_function_collapse_HXX

#include <vector>
#include <iostream>

#include "constraint.hxx"
#include "tile.hxx"

namespace wfc{

class wave_function_collapse
{
private:
    /* data */
public:
    wave_function_collapse(char states[], std::vector<wfc::constraint> constraints);
    ~wave_function_collapse();
};

wave_function_collapse::wave_function_collapse(char states[], std::vector<wfc::constraint>)
{
    std::cout << "Constructing wave_function_collapse object" << std::endl;
}

wave_function_collapse::~wave_function_collapse()
{
    // destructor
}

} // namespace wfc

#endif // WaveFC_wfclib_wave_function_collapse_HXX