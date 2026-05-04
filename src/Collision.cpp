#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB) {
  return SDL_HasIntersection(&recA, &recB);
}

bool Collision::AABB(const ColliderComponent &colA,
                     const ColliderComponent &colB) {
  // Allegedly the player can collide with itself?
  // if(colA.tag == colB.tag) return false;

  return AABB(colA.collider, colB.collider);
}