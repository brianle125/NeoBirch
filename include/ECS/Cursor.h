#ifndef CURSOR_H
#define CURSOR_H

#include "ECS.h"
#include "TransformComponent.h"
#include "Vector2D.h"

class Cursor : public Component {
public:
    void init() override {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {}

    Vector2D getCursorPosition() {
        return transform->position;
    }
private:
    TransformComponent* transform;
    Vector2D pos;
};

#endif