#include "ECS/ColliderComponent.h"

ColliderComponent::ColliderComponent(std::string t) { tag = t; }

ColliderComponent::ColliderComponent(std::string t, int xpos, int ypos,
                                     int size) {
  tag = t;
  collider.x = xpos;
  collider.y = ypos;
  collider.h = collider.w = size;
}

ColliderComponent::ColliderComponent(std::string t, int xpos, int ypos, int w,
                                     int h) {
  tag = t;
  collider.x = xpos;
  collider.y = ypos;
  collider.w = w;
  collider.h = h;
}

void ColliderComponent::init() {
  if (!entity->hasComponent<TransformComponent>()) {
    entity->addComponent<TransformComponent>();
  }

  transform = &entity->getComponent<TransformComponent>();

  tex = TextureManager::LoadTexture("assets/coltex.png");
  srcR = {0, 0, Config::TILE_SIZE, Config::TILE_SIZE};
  destR = {collider.x, collider.y, collider.w, collider.h};
}

void ColliderComponent::update() {
  if (tag != "terrain") {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }

  destR = {collider.x - Game::camera.x, collider.y - Game::camera.y,
           collider.w, collider.h};
}

void ColliderComponent::draw() {
  TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}