#include "genesis/exiting/application_exiter.hpp"
#include "genesis/exiting/exit_event.hpp"

namespace genesis
{
ApplicationExiter::ApplicationExiter(SharedPointer<Input> input)
    : input_(input), exit_event_type_(SDL_RegisterEvents(1)) { }

void ApplicationExiter::Update(float delta)
{
    if (!input_->IsKeyPressedThisFrame(SDLK_ESCAPE))
        return;

    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));

    event.type = exit_event_type_;
    event.user.code = GENESIS_EXIT_CODE;
    SDL_PushEvent(&event);
}
}