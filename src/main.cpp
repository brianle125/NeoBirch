#include "Config.h"
#include "Game.h"

using namespace Config;

// Game *game = nullptr;
std::unique_ptr<Game> game;

int main(int argc, char *argv[]) {

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  game = std::make_unique<Game>();
  game->init("BirchEngine Revamped", WINDOW_WIDTH, WINDOW_HEIGHT, false);

  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
  return 0;
}