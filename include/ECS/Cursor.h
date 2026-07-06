#ifndef CURSOR_H
#define CURSOR_H

#include "ECS.h"
#include "TransformComponent.h"
#include "Vector2D.h"

#include <numbers>

class Cursor : public Component {
public:
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        pos = Vector2D(0.0f, 0.0f);
    }

    void update() override {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        Vector2D target(static_cast<float>(mouseX) + Game::camera.x,
                        static_cast<float>(mouseY) + Game::camera.y);
                        
        pos = target;
    }

    void draw() override {
        Vector2D playerPos = transform->position;
        // Change depending on sprite resolution
        float centerOffsetX = 16.0f * transform->scale;
        float centerOffsetY = 16.0f * transform->scale;
        Vector2D playerCenter = playerPos + Vector2D(centerOffsetX, centerOffsetY);
        Vector2D direction = pos - playerCenter;
        int aimerLength = 200;

        Vector2D normalizedDirection = direction.normalize();
        Vector2D endPoint = (playerCenter + (normalizedDirection * aimerLength));
        int startX = static_cast<int>(playerCenter.x - Game::camera.x);
        int startY = static_cast<int>(playerCenter.y - Game::camera.y);
        int endX = static_cast<int>(endPoint.x - Game::camera.x);
        int endY = static_cast<int>(endPoint.y - Game::camera.y);

        SDL_Surface* surface = IMG_Load("assets/window.png"); 
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface); 
        SDL_FreeSurface(surface);

        SDL_Rect dest;
        dest.x = startX;
        dest.y = startY;
        dest.w = 200;
        dest.h = 200;

        float angle = std::atan2(normalizedDirection.y, normalizedDirection.x) * 180.0f / std::numbers::pi_v<float>;

        SDL_Point center = {static_cast<int>(centerOffsetX), static_cast<int>(centerOffsetY)};

        

        // SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        // SDL_RenderDrawLine(Game::renderer, startX, startY, endX, endY);
        SDL_RenderCopyEx(Game::renderer, texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);
    }

    Vector2D getCursorPosition() {
        return transform->position;
    }
private:
    TransformComponent* transform;
    Vector2D pos;
};

#endif