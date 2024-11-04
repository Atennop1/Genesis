#include "genesis/physics/physics_simulation.hpp"
#include <algorithm>
#include <list>

namespace genesis
{
void PhysicsSimulation::Update(float delta)
{
    elapsed_time_ += delta;

    while (last_update_time_ < elapsed_time_)
    {
        std::list<std::pair<IPhysicsObject*, IPhysicsObject*>> collisions { };
        objects_.erase(std::remove_if(objects_.begin(), objects_.end(), [](auto physics_object) { return physics_object->IsDestroyed(); }), objects_.end());

        for (auto physics_object : objects_)
        {
            physics_object->Properties().velocity = physics_object->Properties().velocity + physics_object->Properties().acceleration * time_step_;
            physics_object->Properties().position = physics_object->Properties().position + physics_object->Properties().velocity * time_step_;
        }

        for (auto object1 : objects_)
        {
            for (auto object2 : objects_)
            {
                if (object1 == object2 || std::find_if(collisions.begin(), collisions.end(), [&](auto pair) { return pair.first == object1.Get(); }) != collisions.end())
                    continue;

                if (object1->Properties().Right() >= object2->Properties().Left() && object1->Properties().Left() <= object2->Properties().Right() && object1->Properties().Bottom() >= object2->Properties().Top() && object1->Properties().Top() <= object2->Properties().Bottom())
                    collisions.emplace_back(object1.Get(), object2.Get());
            }
        }

        for (auto collision : collisions)
            collision.first->HandleCollisionStart(collision.second);

        last_update_time_ += time_step_;
    }
}

void PhysicsSimulation::Add(SharedPointer<IPhysicsObject> &object)
{
    if (std::find(objects_.begin(), objects_.end(), object) == objects_.end())
        objects_.push_back(object);
}

void PhysicsSimulation::Remove(SharedPointer<IPhysicsObject> &object)
{
    if (auto find_iterator = std::find(objects_.begin(), objects_.end(), object); find_iterator != objects_.end())
        objects_.erase(find_iterator);
}
}
