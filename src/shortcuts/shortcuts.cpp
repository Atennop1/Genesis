#include "genesis/shortcuts/shortcuts.hpp"

namespace genesis
{
SDL_FRect Shortcuts::PhysicalPropertiesToRect(SDL_Window* window, PhysicalProperties properties)
{
    SDL_FRect rect;
    rect.x = properties.Left();
    rect.w = properties.size.x;
    rect.h = properties.size.y;

    int window_height = 0;
    SDL_GetWindowSize(window, NULL, &window_height);
    rect.y = window_height - properties.Top();
    return rect;
}

SDL_FRect Shortcuts::PositionAndSizeToRect(SDL_Window* window, Vector2 position, Vector2 size)
{
    SDL_FRect rect;
    rect.x = position.x - size.x / 2.0f;
    rect.w = size.x;
    rect.h = size.y;

    int window_height = 0;
    SDL_GetWindowSize(window, NULL, &window_height);
    rect.y = window_height - position.y - size.y / 2.0f;
    return rect;
}

SDL_FRect Shortcuts::PositionAndTextureToRect(SDL_Window* window, Vector2 position, SDL_Texture *texture, float position_multiplier, float size_multiplier)
{
    // 70 166

    int width = 0; // 15
    int height = 0; // 7
    SDL_FRect rect = { };
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    rect.h = (float)height * size_multiplier; //42
    rect.w = (float)width * size_multiplier; // 60
    rect.x = position.x * position_multiplier - rect.w / 2.0f; // 390

    int window_height = 0; //1080
    SDL_GetWindowSize(window, NULL, &window_height);
    rect.y = window_height - position.y * position_multiplier - rect.h / 2.0f; // 63
    return rect;
}
}
