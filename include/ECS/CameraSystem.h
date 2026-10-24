#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include <SDL.h>

static constexpr int xOffset = 400;
static constexpr int yOffset = 320;

class CameraSystem : public System {
public:
    CameraSystem(SDL_Rect& cam);

    void update(std::vector<Entity*>& players) override;
private:
    SDL_Rect& camera;
};