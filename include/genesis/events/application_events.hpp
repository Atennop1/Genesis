#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_APPLICATION_EVENTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_APPLICATION_EVENTS_HPP_

#include "genesis/loop/objects/game_loop_object.hpp"
#include <SDL.h>
#include <list>
#include <vector>

namespace genesis
{
class ApplicationEvents : public IGameLoopObject
{
public:
    void Update(float delta) override;

    std::vector<SDL_Event*> GetEventsOfType(std::vector<Uint32> types);
    std::vector<SDL_Event*> GetEventsOfType(Uint32 type) { return GetEventsOfType(std::vector<Uint32>{type}); }

private:
    std::list<SDL_Event> events_ = { };
};
}

#endif