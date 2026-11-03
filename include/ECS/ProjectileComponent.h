#pragma once

#include "../Vector2D.h"
#include "../Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include <iostream>

static constexpr const char* PROJECTILE = "projectile";

class ProjectileComponent : public Component {
public:
  ProjectileComponent(int rng, int sp, Vector2D vel);
  ~ProjectileComponent() override;

  void init() override;
  void update() override;

  const int getDamage();

private:
  TransformComponent *transform;
  int range = 0;
  int speed = 0;
  int distance = 0;
  int damage = 100;
  Vector2D velocity;
};
