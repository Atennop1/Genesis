#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_OBJECTS_GAME_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_OBJECTS_GAME_OBJECT_HPP_

#include "genesis/loop/objects/game_loop_object.hpp"
#include "genesis/physics/physical_properties.hpp"
#include "genesis/physics/physics_object.hpp"

namespace genesis
{
class IGameObject : public IGameLoopObject, public IPhysicsObject
{
public:
    IGameObject(PhysicalProperties properties) : properties_(properties) { }
    virtual ~IGameObject() = default;

    virtual void Update(float delta) { }
    virtual void FixedUpdate(float fixed_delta) { }

    virtual void HandleCollisionStart(IPhysicsObject* other) { }
    virtual PhysicalProperties& Properties() { return properties_; }

    virtual void Destroy() { is_destroyed_ = true; }
    virtual bool IsDestroyed() { return is_destroyed_; }

private:
    bool is_destroyed_ = false;
    PhysicalProperties properties_;
};
}

#endif
