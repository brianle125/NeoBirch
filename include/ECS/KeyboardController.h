#pragma once

#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h"

// Direction enum for movement
enum Direction { 
  DIR_NONE = 0, 
  DIR_POSITIVE = 1, 
  DIR_NEGATIVE = -1 
};

class KeyboardController : public Component {
public:
  TransformComponent *transform;
  ShootingComponent *shooter;
  SpriteComponent *sprite;

    void init() override;
    void update() override;

private:
  // Params for rate of fire
  Uint32 lastShotTime = 0;
  Uint32 shotCooldown = 250;
};