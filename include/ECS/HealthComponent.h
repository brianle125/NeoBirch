#pragma once

#include "../Config.h"
#include "ECS.h"

static constexpr int DefaultHealth = 30;

class HealthComponent : public Component {
public:
  HealthComponent() : currentHealth(DefaultHealth), maxHealth(DefaultHealth) {}
  HealthComponent(int ch, int mh) : currentHealth(ch), maxHealth(mh) {}
  ~HealthComponent() = default;

  const int getHealth() { return currentHealth; }

  // TODO: This can do for now as the "game" is very simple,
  // but this damage should either be another component or event-based
  void takeDamage(int dmg) { currentHealth -= dmg; }

private:
  int currentHealth;
  int maxHealth;
};