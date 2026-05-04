#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *texture) {
  SDL_Surface *tempSurface = IMG_Load(texture);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);
  if (!tex) {
    std::cout << "Failed to load texture: " << texture
              << " Error: " << SDL_GetError() << std::endl;
  }
  return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest,
                          SDL_RendererFlip flip) {
  if (dest.x < (Game::camera.w + dest.w) && dest.x >= ((-1) * dest.w))
    if (dest.y < (Game::camera.h + dest.h) && dest.y >= ((-1) * dest.h))
      SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, nullptr, flip);
}
