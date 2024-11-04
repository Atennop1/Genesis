#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_APPLICATION_EVENTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_APPLICATION_EVENTS_HPP_

#include "genesis/loop/objects/game_loop_object.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <list>

namespace genesis
{
class ApplicationEvents : public IGameLoopObject
{
public:
    void Update(float delta) override;

    std::vector<SDL_Event*> GetEventsOfTypes(std::vector<Uint32> types);
    std::vector<SDL_Event*> GetEventsOfTypes(Uint32 type) { return GetEventsOfTypes(std::vector<Uint32>{type}); }

    std::vector<SDL_Event*> GetEventsWithCodes(std::vector<Uint32> codes);
    std::vector<SDL_Event*> GetEventsWithCodes(Uint32 code) { return GetEventsWithCodes(std::vector<Uint32>{code}); }

private:
    std::list<SDL_Event> events_ = { };
};
}

#endif