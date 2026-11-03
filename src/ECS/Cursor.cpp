#include "ECS/Cursor.h"

#include "Game.h"

#include <cmath>

void Cursor::init() {
  transform = &entity->getComponent<TransformComponent>();
  texture = TextureManager::LoadTexture("assets/aimer.png");
  pos = Vector2D(0.0f, 0.0f);
}

void Cursor::update() {
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  Vector2D target(static_cast<float>(mouseX) + Game::camera.x,
                  static_cast<float>(mouseY) + Game::camera.y);

  pos = target;
}

void Cursor::draw() {
  Vector2D playerPos = transform->position;

  float centerOffsetX = (Config::SPRITE_RESOLUTION / 2) * transform->scale;
  float centerOffsetY = (Config::SPRITE_RESOLUTION / 2) * transform->scale;
  Vector2D playerCenter = playerPos + Vector2D(centerOffsetX, centerOffsetY);
  Vector2D direction = pos - playerCenter;
  int aimerLength = 200;

  Vector2D normalizedDirection = direction.normalize();
  Vector2D endPoint = playerCenter + (normalizedDirection * aimerLength);
  int startX = static_cast<int>(playerCenter.x - Game::camera.x);
  int startY = static_cast<int>(playerCenter.y - Game::camera.y);
  int endX = static_cast<int>(endPoint.x - Game::camera.x);
  int endY = static_cast<int>(endPoint.y - Game::camera.y);

  SDL_Rect dest;
  int aimerW, aimerH;

  if (SDL_QueryTexture(texture, NULL, NULL, &aimerW, &aimerH) == 0) {
    dest.w = static_cast<int>(aimerW / 2);
    dest.h = static_cast<int>(aimerH);
  } else {
    aimerH = aimerLength;
    dest.w = aimerLength;
    dest.h = aimerLength;
  }

  dest.x = startX;
  dest.y = startY - dest.h / 2;

  SDL_Point center = {0, dest.h / 2};

  float angle = std::atan2(normalizedDirection.y, normalizedDirection.x) *
                180.0f / std::numbers::pi_v<float>;

  SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  SDL_RenderCopyEx(Game::renderer, texture, NULL, &dest, angle, &center,
                   SDL_FLIP_NONE);
}

Vector2D Cursor::getCursorPosition() { return transform->position; }