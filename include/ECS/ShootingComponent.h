#pragma once
#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include <cmath>

class ShootingComponent : public Component {
public:
  void init() override;
  void playerShoot(const Vector2D &target);

private:
  TransformComponent *transform;
};