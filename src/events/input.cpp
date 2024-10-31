#include "genesis/events/input.hpp"
#include <algorithm>

namespace genesis
{
Input::Input(SharedPointer<ApplicationEvents> events)
    : events_(events) { }

void Input::Update(float delta)
{
    pressed_this_frame_keys_.clear();
    std::vector<SDL_Event*> events = events_->GetEventsOfType({ SDL_KEYDOWN, SDL_KEYUP });

    for (auto event : events)
    {
        if (event->type == SDL_KEYUP)
        {
            pressed_keys_.remove(event->key.keysym.sym);
            continue;
        }

        pressed_this_frame_keys_.push_back(event->key.keysym.sym);
        pressed_keys_.push_back(event->key.keysym.sym);
    }
}

bool Input::IsKeyPressed(const SDL_Keycode key_type) const
    { return std::find(pressed_keys_.begin(), pressed_keys_.end(), key_type) != pressed_keys_.end(); }

bool Input::IsKeyPressedThisFrame(const SDL_Keycode key_type) const
    { return std::find(pressed_this_frame_keys_.begin(), pressed_this_frame_keys_.end(), key_type) != pressed_this_frame_keys_.end(); }
}