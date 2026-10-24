#pragma once

#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h"

#include <SDL_gamecontroller.h>

static constexpr int JOYSTICK_DEAD_ZONE = 4000;

namespace Gamepad {
  enum Direction { 
    DIR_NONE = 0, 
    DIR_POSITIVE = 1, 
    DIR_NEGATIVE = -1 
  };
}


class GamepadController : public Component {
public:
  ~GamepadController() override;
  void onControllerDisconnected();
  void processMovement();
  void init() override;
  void update() override;

private:
  SDL_GameController *findController();

  TransformComponent *transform;
  ShootingComponent *shooter;
  SpriteComponent *sprite;
  SDL_GameController* controller;
};