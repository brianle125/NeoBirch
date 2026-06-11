#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

#include <SDL.h>
#include <vector>

class ProjectileSystem : public System {
public:
    ProjectileSystem(std::vector<Entity*>& projectiles) : projectiles(projectiles) {}
    void update(std::vector<Entity*>& entities) override {
        for (auto &entity : entities) {
            for (auto &proj : projectiles) {
                if (Collision::AABB(
                        entity->getComponent<ColliderComponent>().collider,
                        proj->getComponent<ColliderComponent>().collider)) {
                    proj->destroy();
                }
            }
        }
    }
private:
    std::vector<Entity*>& projectiles;
};