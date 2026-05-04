#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include <memory>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  bool running() { return isRunning; }
  void render();

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static SDL_Rect camera;
  static std::unique_ptr<AssetManager> assets;
  enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupColliders,
    groupProjectiles
  };

private:
  SDL_Window *window;
};