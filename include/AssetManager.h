#pragma once

#include "ECS/ECS.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include <SDL.h>

#include <map>
#include <string>

enum class TextureId {
  Terrain,
  Player,
  Projectile
};

enum class FontId {
  Arial
};

enum class FontSize : int {
  Small = 12,
  Regular = 16,
  Large = 24,
  Title = 32
};

class AssetManager {
public:
  AssetManager(Manager *man);
  ~AssetManager();

  // gameobjects
  void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed,
                        TextureId textureId);

  // texture management
  void AddTexture(TextureId id);
  SDL_Texture *GetTexture(TextureId id);

  void AddFont(FontId id, FontSize fontSize = FontSize::Regular);
  TTF_Font *GetFont(FontId id);

private:
  Manager *manager;
  std::map<TextureId, SDL_Texture *> textures;
  std::map<FontId, TTF_Font *> fonts;
};