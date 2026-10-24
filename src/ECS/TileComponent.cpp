#include "ECS/TileComponent.h"

TileComponent::TileComponent() = default;

TileComponent::~TileComponent() = default;

TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize,
                             int tscale, TextureId id) {
  texture = Game::assets->GetTexture(id);

  srcRect.x = srcX;
  srcRect.y = srcY;
  srcRect.w = srcRect.h = tsize;
  position.x = static_cast<float>(xpos);
  position.y = static_cast<float>(ypos);
  destRect.w = destRect.h = tsize * tscale;
}

void TileComponent::update() {
  destRect.x = static_cast<int>(position.x - Game::camera.x);
  destRect.y = static_cast<int>(position.y - Game::camera.y);
}

void TileComponent::draw() {
  TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
}