#pragma once

#include "../Config.h"
#include "ECS.h"

static constexpr int DefaultHealth = 30;

class HealthComponent : public Component {
public:
  HealthComponent();
  HealthComponent(int ch, int mh);
  ~HealthComponent();

  const int getHealth();

  // TODO: This can do for now as the "game" is very simple,
  // but this damage should either be another component or event-based
  void takeDamage(int dmg);

private:
  int currentHealth;
  int maxHealth;
};