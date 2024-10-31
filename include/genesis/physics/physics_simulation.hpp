#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_PHYSICS_PHYSICS_SIMULATION_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_PHYSICS_PHYSICS_SIMULATION_HPP_

#include "genesis/physics/physics_object.hpp"
#include "genesis/memory/shared_pointer.hpp"
#include "genesis/loop/objects/game_loop_object.hpp"
#include <vector>

namespace genesis
{
class PhysicsSimulation : public IGameLoopObject
{
public:
    PhysicsSimulation() : PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> { }) { }
    explicit PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &objects) : objects_(objects) { }
    explicit PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &&objects) : PhysicsSimulation(objects) { }

    virtual void Update(float delta) override;
    void Add(SharedPointer<IPhysicsObject> &object);
    void Remove(SharedPointer<IPhysicsObject> &object);

    void Add(IPhysicsObject &object) { Add(SharedPointer(&object)); }
    void Add(SharedPointer<IPhysicsObject> &&object) { Add(object); }
    void Remove(IPhysicsObject &object) { Remove(SharedPointer(&object)); }
    void Remove(SharedPointer<IPhysicsObject> &&object) { Remove(object); }

private:
    float elapsed_time_ = 0.0f;
    float last_update_time_ = 0.0f;

    const float time_step_ = 1.0f / 60.0f;
    std::vector<SharedPointer<IPhysicsObject>> objects_ = { };
};
}

#endif
