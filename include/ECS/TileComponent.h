#pragma once

#include "../AssetManager.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../Vector2D.h"
#include "ECS.h"

class TileComponent : public Component {
public:
  TileComponent();
  ~TileComponent() override;

  TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale,
                TextureId id);

  void update() override;
  void draw() override;
private:
  SDL_Texture *texture;
  SDL_Rect srcRect, destRect;
  Vector2D position;
};