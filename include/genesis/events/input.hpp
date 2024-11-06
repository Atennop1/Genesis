#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_INPUT_INPUT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_INPUT_INPUT_HPP_

#include "genesis/loop/objects/game_loop_object.hpp"
#include "genesis/events/application_events.hpp"
#include "genesis/memory/shared_pointer.hpp"
#include <list>

namespace genesis
{
class Input : public IGameLoopObject
{
public:
    Input(SharedPointer<ApplicationEvents> events);

    virtual void Update(float delta) override;
    bool IsKeyPressed(SDL_Keycode key_type) const;
    bool IsKeyPressedThisFrame(SDL_Keycode key_type) const;

private:
    std::list<SDL_Keycode> pressed_keys_ = { };
    std::list<SDL_Keycode> pressed_this_frame_keys_ = { };
    SharedPointer<ApplicationEvents> events_;
};
}

#endif
