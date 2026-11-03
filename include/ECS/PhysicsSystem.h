#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

#include <SDL.h>
#include <vector>


class PhysicsSystem : public System {
public:
    PhysicsSystem(Manager& mgr, std::vector<Entity*>& cols);
    void update(std::vector<Entity*>& movingEntities) override;

private:
    Manager& manager;
    std::vector<Entity*>& colliders;
};