#include "genesis/rendering/screen_applier.hpp"

namespace genesis
{
ScreenApplier::ScreenApplier(WindowReferences window_references)
    : window_references_(window_references) { }

void ScreenApplier::Update(float delta)
{
    SDL_RenderPresent(window_references_.Renderer());
}
}
