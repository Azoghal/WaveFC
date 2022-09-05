#include "tile.hxx"

namespace wfc {
Tile::Tile(/* args */)
{
    collapsed_ = false;
    final_state_ = std::nullopt;
}

Tile::~Tile()
{
    // Destructor
}

} // namespace wfc
