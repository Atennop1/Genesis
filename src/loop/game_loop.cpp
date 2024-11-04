#include "genesis/loop/game_loop.hpp"
#include "genesis/exiting/exit_event.hpp"
#include <algorithm>

namespace genesis
{
GameLoop::GameLoop(SharedPointer<GameTime> game_time, SharedPointer<ApplicationEvents> events)
    : game_time_(game_time), events_(events) { }

void GameLoop::Activate()
{
    while (true)
    {
        if (!game_time_->IsActive())
            continue;

        float delta = game_time_->Delta();
        objects_.erase(std::remove_if(objects_.begin(), objects_.end(), [](auto updatable) { return updatable->IsDestroyed(); }), objects_.end());

        for (auto &updatable: objects_)
            updatable->Update(delta);

        if (!events_->GetEventsWithCodes(GENESIS_EXIT_CODE).empty())
            break;
    }
}

void GameLoop::Add(SharedPointer<IGameLoopObject> &object)
{
    if (std::find(objects_.begin(), objects_.end(), object) == objects_.end())
        objects_.push_back(object);
}

void GameLoop::Remove(SharedPointer<IGameLoopObject> &object)
{
    if (auto find_iterator = std::find(objects_.begin(), objects_.end(), object); find_iterator != objects_.end())
        objects_.erase(find_iterator);
}
}
