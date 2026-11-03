#pragma once

#include "../TextureManager.h"
#include "../Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "Config.h"

#include <SDL.h>

struct ColliderDefinition {
  int offsetX;
  int offsetY;
  int width;
  int height;
};

class ColliderComponent : public Component {
public:
  SDL_Rect collider;

  ColliderComponent(std::string t);

  ColliderComponent(std::string t, int xpos, int ypos, int size);

  ColliderComponent(std::string t, int xpos, int ypos, int w, int h);

  void init() override;
  void update() override;
  void draw() override;

private:
  std::string tag;
  SDL_Texture *tex;
  SDL_Rect srcR, destR;

  TransformComponent *transform;
};