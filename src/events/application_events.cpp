#include "genesis/events/application_events.hpp"
#include <algorithm>

namespace genesis
{
void ApplicationEvents::Update(float delta)
{
    events_.clear();
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
        events_.push_back(event);
}

std::vector<SDL_Event*> ApplicationEvents::GetEventsOfTypes(std::vector<Uint32> types)
{
    auto result = std::vector<SDL_Event*> { };

    for (auto &event : events_)
        if (std::find_if(types.begin(), types.end(), [&](Uint32 type) { return event.type == type; }) != types.end())
            result.push_back(&event);

    return result;
}

std::vector<SDL_Event *> ApplicationEvents::GetEventsWithCodes(std::vector<Uint32> codes)
{
    auto result = std::vector<SDL_Event*> { };

    for (auto &event : events_)
        if (std::find_if(codes.begin(), codes.end(), [&](Uint32 code) { return event.user.code == code; }) != codes.end())
            result.push_back(&event);

    return result;
}
}
