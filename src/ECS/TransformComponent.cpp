#include "ECS/TransformComponent.h"

TransformComponent::TransformComponent() { position.Zero(); }

TransformComponent::TransformComponent(int sc) {
  position.Zero();
  scale = sc;
}

TransformComponent::TransformComponent(float x, float y) { position.Zero(); }

TransformComponent::TransformComponent(float x, float y, int h, int w, int sc) {
  position.x = x;
  position.y = y;
  height = h;
  width = w;
  scale = sc;
}

void TransformComponent::init() { velocity.Zero(); }

void TransformComponent::update() {
  position.x += static_cast<int>(velocity.x * speed);
  position.y += static_cast<int>(velocity.y * speed);
}