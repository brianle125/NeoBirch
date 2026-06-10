#include "Game.h"
#include "AssetManager.h"
#include "AudioMixer.h"
#include "Collision.h"
#include "Config.h"
#include "ECS/Components.h"
#include "ECS/CameraSystem.h"
#include "ECS/PhysicsSystem.h"
#include "Map.h"
#include "TextureManager.h"
#include "Vector2D.h"

#include <sstream>
#include <format>

using namespace Config;

// Map* map;
std::unique_ptr<Map> map;
Manager manager;
AudioMixer mixer;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = CAMERA_CONFIG;
std::unique_ptr<AssetManager> Game::assets = std::make_unique<AssetManager>(&manager);
bool Game::isRunning = false;

HealthComponent *testPtr = nullptr;

auto &player(manager.addEntity());
auto &label(manager.addEntity());

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

Game::Game() {}

Game::~Game() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::init(const char *title, int width, int height, bool fullscreen) {
  int flags = 0;

  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, flags);

    // Set the icon for the window
    SDL_Surface *iconSurface = IMG_Load("assets/window.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    isRunning = true;
  }

  // Init the font
  if (TTF_Init() == -1) {
    std::cerr << "Error : SDL_TTF" << std::endl;
  }

  // Load Textures and font
  assets->AddTexture(TextureId::Terrain);
  assets->AddTexture(TextureId::Player);
  assets->AddTexture(TextureId::Projectile);
  assets->AddFont(FontId::Arial);

  map = std::make_unique<Map>(TextureId::Terrain, MAP_SCALE, TILE_SIZE);
  map->LoadMap("assets/map.map", 25, 20);

  // Components must be added in ordered sequence.
  player.addComponent<TransformComponent>(PLAYER_START_X, PLAYER_START_Y,
                                          PLAYER_HEIGHT, PLAYER_WIDTH,
                                          PLAYER_SCALE);
  player.addComponent<SpriteComponent>(TextureId::Player, true);
  player.addComponent<ShootingComponent>();
  player.addComponent<ColliderComponent>("player");
  player.addComponent<HealthComponent>(PLAYER_HEALTH, PLAYER_HEALTH);
  player.addComponent<KeyboardController>();
  player.addComponent<GamepadController>();
  player.addGroup(groupPlayers);

  SDL_Color white = {255, 255, 255, 255};
  label.addComponent<UILabel>(10, 10, "Loading...", FontId::Arial, white);

  cameraSystem = std::make_unique<CameraSystem>(camera);
  physicsSystem = std::make_unique<PhysicsSystem>(manager, colliders);

  // These are here to test projectile/player collision
	// assets->CreateProjectile(Vector2D(600, 600), Vector2D(2,0),200, 2, TextureId::Projectile);
	// assets->CreateProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, TextureId::Projectile);
}

void Game::handleEvents() {
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_CONTROLLERDEVICEREMOVED:
        player.getComponent<GamepadController>().onControllerDisconnected();
        break;
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
    }
  }
}

void Game::update() {
  std::stringstream ss;
  // Check if there are any active players
  bool anyPlayerActive = false;
  for (auto &p : players) {
    if (p->isActive()) {
      ss << "Health: " << p->getComponent<HealthComponent>().getHealth();
      label.getComponent<UILabel>().SetLabelText(ss.str(), FontId::Arial);
      anyPlayerActive = true;
      break;
    }
  }

  if (!anyPlayerActive) {
    for (auto &p : players) {
      p->removeComponent<SpriteComponent>();
    }
    ss << "Game Over!";
    mixer.playSound(GAME_OVER);
    label.getComponent<UILabel>().SetLabelText(ss.str(), FontId::Arial);
    return;
  }

  manager.refresh();
  manager.update();

  physicsSystem->update(players);
  for (auto &playerEntity : players) {
    for (auto &proj : projectiles) {
      if (Collision::AABB(
              playerEntity->getComponent<ColliderComponent>().collider,
              proj->getComponent<ColliderComponent>().collider)) {
        std::cout << "Hit player!" << std::endl;
        proj->destroy();
        
        // Optionally handle health/damage here
        playerEntity->getComponent<HealthComponent>().takeDamage(5);
        // playerEntity->destroy();
      }
    }
  }

  cameraSystem->update(players);
}

void Game::render() {
  SDL_RenderClear(renderer);
  for (auto &t : tiles) {
    t->draw();
  }

  for (auto &c : colliders) {
    c->draw();
  }

  for (auto &p : players) {
    p->draw();
  }

  for (auto &p : projectiles) {
    p->draw();
  }

  label.draw();
  SDL_RenderPresent(renderer);
}