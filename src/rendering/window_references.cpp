#include "genesis/rendering/window_references.hpp"

namespace genesis
{
WindowReferences::WindowReferences(SDL_Window *window, SDL_Renderer *renderer)
    : window(window), renderer(renderer) { }
}