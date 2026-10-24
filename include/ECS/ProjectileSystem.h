#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

#include <SDL.h>
#include <vector>

class ProjectileSystem : public System {
public:
    ProjectileSystem(std::vector<Entity*>& projectiles);
    void update(std::vector<Entity*>& entities) override;
private:
    std::vector<Entity*>& projectiles;
};