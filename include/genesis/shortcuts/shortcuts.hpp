#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_SHORTCUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_TOOLS_SHORTCUTS_SHORTCUTS_HPP_

#include "genesis/physics/physical_properties.hpp"
#include <SDL.h>

namespace genesis
{
class Shortcuts
{
public:
    static SDL_FRect PhysicalPropertiesToRect(PhysicalProperties properties);
    static SDL_FRect PositionAndSizeToRect(Vector2 position, Vector2 size);
    static SDL_FRect PositionAndTextureToRect(Vector2 position, SDL_Texture *texture, float position_multiplier = 1, float size_multiplier = 1);
};
}

#endif
