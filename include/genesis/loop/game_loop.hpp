#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_GAME_LOOP_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_GAME_LOOP_HPP_

#include "genesis/loop/game_time.hpp"
#include "genesis/memory/shared_pointer.hpp"
#include "genesis/events/application_events.hpp"
#include <vector>

namespace genesis
{
class GameLoop
{
public:
    GameLoop(SharedPointer<GameTime> game_time, SharedPointer<ApplicationEvents> events);
    void Activate();

    void Add(SharedPointer<IGameLoopObject> &object);
    void Remove(SharedPointer<IGameLoopObject> &object);

    void Add(IGameLoopObject &object) { Add(SharedPointer<IGameLoopObject>(&object)); }
    void Add(SharedPointer<IGameLoopObject> &&object) { Add(object); }
    void Remove(IGameLoopObject &object) { Remove(SharedPointer<IGameLoopObject>(&object)); }
    void Remove(SharedPointer<IGameLoopObject> &&object) { Remove(object); }

private:
    bool is_active_ = true;
    SharedPointer<GameTime> game_time_;

    SharedPointer<ApplicationEvents> events_;
    std::vector<SharedPointer<IGameLoopObject>> objects_ = { };
};
}

#endif
