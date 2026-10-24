#pragma once

#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "Animation.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"
#include <map>

class SpriteComponent : public Component {
private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;

  bool animated = false;
  int frames = 0;
  int speed = 100;

public:
  int animIndex = 0;
  std::map<std::string, Animation> animations;

  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent();
  SpriteComponent(TextureId id);

  SpriteComponent(TextureId id, bool isAnimated);

  ~SpriteComponent() override;

  void setTex(TextureId id);

  void init() override;
  void update() override;
  void draw() override;
  void Play(const std::string animName);
};