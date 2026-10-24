#include "ECS/Animation.h"

Animation::Animation() = default;

Animation::Animation(int i, int f, int s) {
  index = i;
  frames = f;
  speed = s;
}