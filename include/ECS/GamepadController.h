#pragma once

#include "../Game.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h"

#include <SDL_gamecontroller.h>

static constexpr int AXIS_X = 0;
static constexpr int AXIS_Y = 1;
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
  ~GamepadController() {
    SDL_GameControllerClose(controller);
  }

  SDL_GameController *findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            return SDL_GameControllerOpen(i);
        }
    }

    return nullptr;
  }

  void processMovement() {
    // Joystick
    Sint16 xAxis = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 yAxis = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);

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

    // D-pad
    if(SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP)) {
      transform->velocity.y = Gamepad::DIR_NEGATIVE;
    }
    else if(SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
      transform->velocity.y = Gamepad::DIR_POSITIVE;
    } 
    else if(SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
      transform->velocity.x = Gamepad::DIR_POSITIVE;
    } 
    else if(SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
      transform->velocity.x = Gamepad::DIR_NEGATIVE;
    }
    
    
    if(transform->velocity.x != 0 || transform->velocity.y != 0) {
        sprite->Play("Walk");
    } else {
        transform->velocity.x = 0;
        transform->velocity.y = 0;
        sprite->Play("Idle");
    }
  }

  void processButtons() {    
    
  }


  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    shooter = &entity->getComponent<ShootingComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
    controller = findController();

    if(!controller) {
      std::cerr << "Unable to read controller!" << std::endl;
    }
  }

  void update() override {
    processMovement();
  }

private:
  TransformComponent *transform;
  ShootingComponent *shooter;
  SpriteComponent *sprite;
  SDL_GameController* controller;
};