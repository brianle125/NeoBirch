#ifndef CURSOR_H
#define CURSOR_H

#include "ECS.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Config.h"

#include <numbers>


class Cursor : public Component {
public:
    void init() override;
    void update() override;
    void draw() override;

    Vector2D getCursorPosition();
private:
    TransformComponent* transform;
    Vector2D pos;
    SDL_Texture* texture;
};

#endif