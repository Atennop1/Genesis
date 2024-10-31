#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_OBJECTS_GAME_LOOP_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_OBJECTS_GAME_LOOP_OBJECT_HPP_

namespace genesis
{
class IGameLoopObject
{
public:
    virtual ~IGameLoopObject() = default;
    virtual void Update(float delta) = 0;

    virtual void Destroy() { is_destroyed_ = true; }
    virtual bool IsDestroyed() { return is_destroyed_; }

private:
    bool is_destroyed_ = false;
};
}

#endif
