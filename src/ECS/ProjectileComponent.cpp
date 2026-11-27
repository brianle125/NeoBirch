#include "ECS/ProjectileComponent.h"
#include "Logger.h"

ProjectileComponent::ProjectileComponent(int rng, int sp, Vector2D vel)
    : range(rng), speed(sp), velocity(vel) {}

ProjectileComponent::~ProjectileComponent() = default;

void ProjectileComponent::init() {
  transform = &entity->getComponent<TransformComponent>();
  transform->velocity = velocity;
}

void ProjectileComponent::update() {
  distance += speed;

  if (distance > range) {
    Logger::Info("Out of Range");
    entity->destroy();
  } else if (transform->position.x > Game::camera.x + Game::camera.w ||
             transform->position.x < Game::camera.x ||
             transform->position.y > Game::camera.y + Game::camera.h ||
             transform->position.y < Game::camera.y) {
    Logger::Info("Out of bounds!");
    entity->destroy();
  }
}

const int ProjectileComponent::getDamage() { return damage; }