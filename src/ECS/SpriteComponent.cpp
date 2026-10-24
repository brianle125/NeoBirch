#include "ECS/SpriteComponent.h"

SpriteComponent::SpriteComponent() = default;

SpriteComponent::SpriteComponent(TextureId id) { setTex(id); }

SpriteComponent::SpriteComponent(TextureId id, bool isAnimated) {
  animated = isAnimated;

  Animation idle = Animation(0, 3, 100);
  Animation walk = Animation(1, 8, 100);

  animations.emplace("Idle", idle);
  animations.emplace("Walk", walk);
  Play("Idle");

  setTex(id);
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::setTex(TextureId id) {
  texture = Game::assets->GetTexture(id);
}

void SpriteComponent::init() {
  transform = &entity->getComponent<TransformComponent>();
  srcRect.x = srcRect.y = 0;
  srcRect.w = transform->width;
  srcRect.h = transform->height;
}

void SpriteComponent::update() {
  if (animated && speed > 0 && frames > 0) {
    srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
  } else {
    srcRect.x = 0;
  }

  srcRect.y = animIndex * transform->height;

  destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
  destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
  destRect.w = transform->width * transform->scale;
  destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw() {
  TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
}

void SpriteComponent::Play(const std::string animName) {
  frames = animations[animName].frames;
  animIndex = animations[animName].index;
  speed = animations[animName].speed;
}