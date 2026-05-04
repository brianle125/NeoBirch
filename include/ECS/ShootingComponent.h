#pragma once
#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include <cmath>

class ShootingComponent : public Component {
public:
  void init() override {
    transform = &entity->getComponent<TransformComponent>();
  }

  void playerShoot(const Vector2D &target) {
    Vector2D playerPos = transform->position;
    // Change depending on sprite resolution
    float centerOffsetX = 16.0f * transform->scale;
    float centerOffsetY = 16.0f * transform->scale;
    Vector2D playerCenter = playerPos + Vector2D(centerOffsetX, centerOffsetY);
    Vector2D direction = target - playerCenter;

    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f) {
      direction.x /= length;
      direction.y /= length;
    }
    float projectileOffset = 120.0f;
    Vector2D spawnPos = playerCenter + (direction * projectileOffset);

    // Fire the projectile
    Game::assets->CreateProjectile(spawnPos, direction * 10.0f, 2000, 2,
                                   TextureId::Projectile);
  }

private:
  TransformComponent *transform;
};