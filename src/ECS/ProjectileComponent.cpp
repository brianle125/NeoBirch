#include "ECS/ProjectileComponent.h"

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
    std::cout << "Out of Range" << std::endl;
    entity->destroy();
  } else if (transform->position.x > Game::camera.x + Game::camera.w ||
             transform->position.x < Game::camera.x ||
             transform->position.y > Game::camera.y + Game::camera.h ||
             transform->position.y < Game::camera.y) {
    std::cout << "Out of bounds!" << std::endl;
    entity->destroy();
  }
}

const int ProjectileComponent::getDamage() { return damage; }