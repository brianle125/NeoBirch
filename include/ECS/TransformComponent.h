#pragma once
#include "../Vector2D.h"
#include "ECS.h"

class TransformComponent : public Component {
public:
  Vector2D position;
  Vector2D velocity;

  int height = 32;
  int width = 32;
  int scale = 1;

  int speed = 3;

  bool blocked = false;

  TransformComponent();

  TransformComponent(int sc);

  TransformComponent(float x, float y);

  TransformComponent(float x, float y, int h, int w, int sc);

  void init() override;
  void update() override;
};