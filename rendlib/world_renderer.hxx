#ifndef WaveFC_rendlib_world_renderer_HXX
#define WaveFC_rendlib_world_renderer_HXX

#include <vector>
#include <unordered_map>
#include <iterator>
#include <string>

namespace renderer {

// Enum for the different tiles?

class WorldRenderer
{
private:
    /* data */
    int width_, height_;
    std::vector<std::vector<int>> world_map_;
    std::unordered_map<int, std::string> colourmap_;
    static std::unordered_map<int, char> sizemap_;
    
public:
    WorldRenderer(int width, int height);
    ~WorldRenderer();
    void PrintWorld();
    void SetWorld();
    void SetWorld(std::vector<std::vector<int>> new_world);
    void SetColourmap();
};

} // namespace renderer

#endif // WaveFC_rendlib_world_renderer_HXX