#include "ECS/PhysicsSystem.h"

#include "Collision.h"

PhysicsSystem::PhysicsSystem(Manager &mgr, std::vector<Entity *> &cols)
    : manager(mgr), colliders(cols) {}

void PhysicsSystem::update(std::vector<Entity *> &movingEntities) {
  for (auto &entity : movingEntities) {
    if (!entity->isActive())
      continue;

    auto &transform = entity->getComponent<TransformComponent>();
    auto &collider = entity->getComponent<ColliderComponent>();
    Vector2D oldPos = transform.position;

    transform.position.x += transform.velocity.x;
    collider.update();
    for (auto &c : colliders) {
      if (Collision::AABB(c->getComponent<ColliderComponent>().collider,
                          collider.collider)) {
        transform.position.x = oldPos.x;
        transform.velocity.x = 0;
        collider.update();
        break;
      }
    }

    transform.position.y += transform.velocity.y;
    collider.update();
    for (auto &c : colliders) {
      if (Collision::AABB(c->getComponent<ColliderComponent>().collider,
                          collider.collider)) {
        transform.position.y = oldPos.y;
        transform.velocity.y = 0;
        collider.update();
        break;
      }
    }
  }
}