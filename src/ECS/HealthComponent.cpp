#include "ECS/HealthComponent.h"

HealthComponent::HealthComponent()
    : currentHealth(DefaultHealth), maxHealth(DefaultHealth) {}

HealthComponent::HealthComponent(int ch, int mh)
    : currentHealth(ch), maxHealth(mh) {}

HealthComponent::~HealthComponent() = default;

const int HealthComponent::getHealth() { return currentHealth; }

void HealthComponent::takeDamage(int dmg) { currentHealth -= dmg; }