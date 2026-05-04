#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "ShootingComponent.h"

// Direction enum for movement
enum Direction
{
    DIR_NONE = 0,
    DIR_POSITIVE = 1,
    DIR_NEGATIVE = -1
};

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    ShootingComponent* shooter;
    SpriteComponent *sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        shooter = &entity->getComponent<ShootingComponent>();
    }

    void update() override
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        Vector2D target(
            static_cast<float>(mouseX) + Game::camera.x,
            static_cast<float>(mouseY) + Game::camera.y
        );

        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = DIR_NEGATIVE;
                sprite->Play("Walk");
                break;
            case SDLK_a:
                transform->velocity.x = DIR_NEGATIVE;
                sprite->Play("Walk");
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d:
                transform->velocity.x = DIR_POSITIVE;
                sprite->Play("Walk");
                break;
            case SDLK_s:
                transform->velocity.y = DIR_POSITIVE;
                sprite->Play("Walk");
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = DIR_NONE;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = DIR_NONE;
                sprite->Play("Idle");
                sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_d:
                transform->velocity.x = DIR_NONE;
                sprite->Play("Idle");
                break;
            case SDLK_s:
                transform->velocity.y = DIR_NONE;
                sprite->Play("Idle");
                break;
            case SDLK_p:
                if (shooter) {
                    std::cout << "Fired!" << std::endl;
                    shooter->playerShoot(target);
                }
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
            default:
                break;
            }
        }
    }
};