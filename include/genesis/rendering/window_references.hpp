#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_RENDERING_WINDOW_REFERENCES_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_RENDERING_WINDOW_REFERENCES_HPP_

#include <SDL.h>

namespace genesis
{
struct WindowReferences
{
public:
    WindowReferences(SDL_Window *window, SDL_Renderer *renderer);

    SDL_Window *Window() const { return window; }
    SDL_Renderer *Renderer() const { return renderer; }

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};
}

#endif
