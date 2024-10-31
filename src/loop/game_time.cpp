#include "genesis/loop/game_time.hpp"
#include <SDL.h>

namespace genesis
{
GameTime::GameTime()
{
    last_time_ = SDL_GetPerformanceCounter();
}

float GameTime::Delta()
{
    float delta = (float)(SDL_GetPerformanceCounter() - last_time_) / (float)SDL_GetPerformanceFrequency(); // in seconds
    last_time_ = SDL_GetPerformanceCounter();
    return delta;
}
}
