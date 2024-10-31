#include "genesis/shortcuts/shortcuts.hpp"

namespace genesis
{
SDL_FRect Shortcuts::PhysicalPropertiesToRect(PhysicalProperties properties)
{
    SDL_FRect rect;
    rect.x = properties.Left();
    rect.y = properties.Top();
    rect.w = properties.size.x;
    rect.h = properties.size.y;
    return rect;
}

SDL_FRect Shortcuts::PositionAndSizeToRect(Vector2 position, Vector2 size)
{
    SDL_FRect rect;
    rect.w = size.x;
    rect.h = size.y;
    rect.x = position.x - size.x / 2.0f;
    rect.y = position.y - size.y / 2.0f;
    return rect;
}

SDL_FRect Shortcuts::PositionAndTextureToRect(Vector2 position, SDL_Texture *texture, float position_multiplier, float size_multiplier)
{
    int width = 0;
    int height = 0;
    SDL_FRect rect = { };
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    rect.h = (float)height * size_multiplier;
    rect.w = (float)width * size_multiplier;
    rect.x = position.x * position_multiplier - rect.w / 2.0f;
    rect.y = position.y * position_multiplier - rect.h / 2.0f;
    return rect;
}
}
