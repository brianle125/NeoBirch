#include "AssetManager.h"
#include "ECS/Components.h"

namespace {
  constexpr std::string_view kTexturePaths[] = {
    "assets/terrain_ss.png",
    "assets/player_anims.png",
    "assets/proj.png"
  };

  constexpr std::string_view kFontFamilies[] = {
    "assets/arial.ttf"
  };

  const std::string_view GetTexturePath(TextureId id) {
    return kTexturePaths[static_cast<size_t>(id)];
  }

  const std::string_view GetFontPath(FontId id) {
    return kFontFamilies[static_cast<size_t>(id)];
  }
}

AssetManager::AssetManager(Manager *man) : manager(man) {}

AssetManager::~AssetManager() {
  // Free up allocated resources
  for(auto& texture: textures) {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();
  for (auto &font : fonts) {
    TTF_CloseFont(font.second);
  }
  fonts.clear();
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range,
                                    int speed, TextureId textureId) {
  auto &projectile(manager->addEntity());
  projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
  projectile.addComponent<SpriteComponent>(textureId, false);
  projectile.addComponent<ProjectileComponent>(range, speed, vel);
  projectile.addComponent<ColliderComponent>(PROJECTILE);
  projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(TextureId id) {
  textures.emplace(id, TextureManager::LoadTexture(GetTexturePath(id).data()));
}

SDL_Texture *AssetManager::GetTexture(TextureId id) {
  return textures[id];
}

void AssetManager::AddFont(FontId id, FontSize fontSize) {
  TTF_Font* font = TTF_OpenFont(GetFontPath(id).data(), static_cast<int>(fontSize));
  if(!font) {
    std::cerr << "Unable to open font: " << SDL_GetError() << std::endl; 
  }
  fonts.emplace(id, font);
}

TTF_Font *AssetManager::GetFont(FontId id) { 
  return fonts[id]; 
}
