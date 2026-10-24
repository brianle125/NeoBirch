#include "ECS/GamepadController.h"

GamepadController::~GamepadController() {
  if (controller) {
    SDL_GameControllerClose(controller);
  }
}

void GamepadController::onControllerDisconnected() {
  if (controller) {
    SDL_GameControllerClose(controller);
    controller = nullptr;
  }
}

void GamepadController::processMovement() {
  Sint16 xAxis = SDL_GameControllerGetAxis(
      controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
  Sint16 yAxis = SDL_GameControllerGetAxis(
      controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);

  transform->velocity.x = 0;
  transform->velocity.y = 0;

  if (xAxis < -JOYSTICK_DEAD_ZONE) {
    transform->velocity.x = Gamepad::DIR_NEGATIVE;
    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
  } else if (xAxis > JOYSTICK_DEAD_ZONE) {
    transform->velocity.x = Gamepad::DIR_POSITIVE;
    sprite->spriteFlip = SDL_FLIP_NONE;
  }

  if (yAxis < -JOYSTICK_DEAD_ZONE) {
    transform->velocity.y = Gamepad::DIR_NEGATIVE;
  } else if (yAxis > JOYSTICK_DEAD_ZONE) {
    transform->velocity.y = Gamepad::DIR_POSITIVE;
  }

  if (SDL_GameControllerGetButton(
          controller,
          SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP)) {
    transform->velocity.y = Gamepad::DIR_NEGATIVE;
  } else if (SDL_GameControllerGetButton(
                 controller,
                 SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
    transform->velocity.y = Gamepad::DIR_POSITIVE;
  } else if (SDL_GameControllerGetButton(
                 controller,
                 SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
    transform->velocity.x = Gamepad::DIR_POSITIVE;
    sprite->spriteFlip = SDL_FLIP_NONE;
  } else if (SDL_GameControllerGetButton(
                 controller,
                 SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
    transform->velocity.x = Gamepad::DIR_NEGATIVE;
    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
  }

  if (transform->velocity.x != 0 || transform->velocity.y != 0) {
    sprite->Play("Walk");
  } else {
    transform->velocity.x = 0;
    transform->velocity.y = 0;
    sprite->Play("Idle");
  }
}

void GamepadController::init() {
  transform = &entity->getComponent<TransformComponent>();
  shooter = &entity->getComponent<ShootingComponent>();
  sprite = &entity->getComponent<SpriteComponent>();
  controller = findController();

  if (!controller) {
    std::cout << "Controller not detected.\n";
  }
}

void GamepadController::update() {
  if (!controller) {
    controller = findController();
    if (!controller)
      return;
    std::cout << "Controller detected.\n";
  }
  processMovement();
}

SDL_GameController *GamepadController::findController() {
  for (int i = 0; i < SDL_NumJoysticks(); i++) {
    if (SDL_IsGameController(i)) {
      return SDL_GameControllerOpen(i);
    }
  }

  return nullptr;
}