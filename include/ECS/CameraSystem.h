#include "ECS.h"
#include "TransformComponent.h"
#include <SDL.h>

static constexpr int xOffset = 400;
static constexpr int yOffset = 320;

class CameraSystem : public System {
public:
    CameraSystem(SDL_Rect& cam) : camera(cam) {}

    void update(std::vector<Entity*>& players) override {

        for(auto& player : players) {
            if(!player->isActive()) continue;
            
            auto& transform = player->getComponent<TransformComponent>();

            // Camera follows the first active player
            camera.x = static_cast<int>(transform.position.x - xOffset);
            camera.y = static_cast<int>(transform.position.y - yOffset);

            if (camera.x < 0) camera.x = 0;
            if (camera.y < 0) camera.y = 0;
            if (camera.x > camera.w) camera.x = camera.w;
            if (camera.y > camera.h) camera.y = camera.h;

            // Only follow the first active player
            break;
            
        }
    }
private:
    SDL_Rect& camera;
};