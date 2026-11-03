#include "ECS/KeyboardController.h"

void KeyboardController::init() {
  transform = &entity->getComponent<TransformComponent>();
  sprite = &entity->getComponent<SpriteComponent>();
  shooter = &entity->getComponent<ShootingComponent>();
}

void KeyboardController::update() {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  Uint32 currentTime = SDL_GetTicks();

  Vector2D target(static_cast<float>(mouseX) + Game::camera.x,
                  static_cast<float>(mouseY) + Game::camera.y);

  const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

  if (keyState[SDL_SCANCODE_W]) {
    transform->velocity.y = DIR_NEGATIVE;
    sprite->Play("Walk");
  } else if (keyState[SDL_SCANCODE_S]) {
    transform->velocity.y = DIR_POSITIVE;
    sprite->Play("Walk");
  } else {
    transform->velocity.y = DIR_NONE;
  }

  if (keyState[SDL_SCANCODE_A]) {
    transform->velocity.x = DIR_NEGATIVE;
    sprite->Play("Walk");
    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
  } else if (keyState[SDL_SCANCODE_D]) {
    transform->velocity.x = DIR_POSITIVE;
    sprite->Play("Walk");
    sprite->spriteFlip = SDL_FLIP_NONE;
  } else {
    transform->velocity.x = DIR_NONE;
  }

  if (!keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_A] &&
      !keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_S]) {
    sprite->Play("Idle");
  }

  if (keyState[SDL_SCANCODE_ESCAPE]) {
    Game::isRunning = false;
  }
}