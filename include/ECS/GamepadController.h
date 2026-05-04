#pragma once

#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h"

#include <SDL_joystick.h>

static constexpr int AXIS_X = 0;
static constexpr int AXIS_Y = 1;
static constexpr int JOYSTICK_DEAD_ZONE = 3000;

namespace Gamepad {
  enum Direction { 
    DIR_NONE = 0, 
    DIR_POSITIVE = 1, 
    DIR_NEGATIVE = -1 
  };
}


class GamepadController : public Component {
public:
  ~GamepadController() {
    SDL_JoystickClose(gamepad);
  }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    shooter = &entity->getComponent<ShootingComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
    gamepad = SDL_JoystickOpen(0);

    if(SDL_NumJoysticks() <= 0 || gamepad == NULL) {
      std::cout << "Unable to read controller!" << std::endl;
    }
  }

  void update() override {
    Sint16 xAxis = SDL_JoystickGetAxis(gamepad, AXIS_X);
    Sint16 yAxis = SDL_JoystickGetAxis(gamepad, AXIS_Y);

    transform->velocity.x = 0;
    transform->velocity.y = 0;

    if (xAxis < -JOYSTICK_DEAD_ZONE) {
      transform->velocity.x = Gamepad::DIR_NEGATIVE;
      sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
    } else if (xAxis > JOYSTICK_DEAD_ZONE) {
        transform->velocity.x = Gamepad::DIR_POSITIVE;
    }


    if (yAxis < -JOYSTICK_DEAD_ZONE) {
        transform->velocity.y = Gamepad::DIR_NEGATIVE;
    }
    else if (yAxis > JOYSTICK_DEAD_ZONE) {
        transform->velocity.y = Gamepad::DIR_POSITIVE;
    }

    
    if(transform->velocity.x != 0 || transform->velocity.y != 0) {
        sprite->Play("Walk");
    } else {
        transform->velocity.x = 0;
        transform->velocity.y = 0;
        sprite->Play("Idle");
    }
}
private:
  TransformComponent *transform;
  ShootingComponent *shooter;
  SpriteComponent *sprite;
  SDL_Joystick* gamepad;

  int xDir;
  int yDir;
};