#include "ECS/ProjectileSystem.h"

#include "Collision.h"

ProjectileSystem::ProjectileSystem(std::vector<Entity *> &projectiles)
    : projectiles(projectiles) {}

void ProjectileSystem::update(std::vector<Entity *> &entities) {
  for (auto &entity : entities) {
    for (auto &proj : projectiles) {
      if (Collision::AABB(entity->getComponent<ColliderComponent>().collider,
                          proj->getComponent<ColliderComponent>().collider)) {
        proj->destroy();
      }
    }
  }
}