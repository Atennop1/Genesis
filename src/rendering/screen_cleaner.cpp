#include "genesis/rendering/screen_cleaner.hpp"

namespace genesis
{
ScreenCleaner::ScreenCleaner(WindowReferences window_references)
    : window_references_(window_references) {}

void ScreenCleaner::Update(float delta)
{
    SDL_SetRenderDrawColor(window_references_.Renderer(), 0, 0, 0, 255);
    SDL_RenderClear(window_references_.Renderer());
}
}
