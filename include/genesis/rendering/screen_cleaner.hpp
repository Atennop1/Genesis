#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_RENDERING_SCREEN_CLEANER_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_RENDERING_SCREEN_CLEANER_HPP_

#include "genesis/rendering/window_references.hpp"
#include "genesis/loop/objects/game_loop_object.hpp"

namespace genesis
{
class ScreenCleaner : public IGameLoopObject
{
public:
    explicit ScreenCleaner(WindowReferences window_references);

    virtual void Update(float delta) override;

private:
    WindowReferences window_references_;
};
}

#endif
