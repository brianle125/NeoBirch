#include "ECS/CameraSystem.h"

CameraSystem::CameraSystem(SDL_Rect &cam) : camera(cam) {}

void CameraSystem::update(std::vector<Entity *> &players) {
  for (auto &player : players) {
    if (!player->isActive())
      continue;

    auto &transform = player->getComponent<TransformComponent>();

    camera.x = static_cast<int>(transform.position.x - xOffset);
    camera.y = static_cast<int>(transform.position.y - yOffset);

    if (camera.x < 0)
      camera.x = 0;
    if (camera.y < 0)
      camera.y = 0;
    if (camera.x > camera.w)
      camera.x = camera.w;
    if (camera.y > camera.h)
      camera.y = camera.h;

    break;
  }
}