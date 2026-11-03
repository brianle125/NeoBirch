#include "ECS/ECS.h"

ComponentID getNewComponentTypeID() {
  static ComponentID lastID = 0u;
  return lastID++;
}

Component::~Component() = default;

void Component::init() {}

void Component::update() {}

void Component::draw() {}

Entity::Entity(Manager &mManager) : manager(mManager) {}

void Entity::update() {
  for (auto &c : components)
    c->update();
}

void Entity::draw() {
  for (auto &c : components)
    c->draw();
}

bool Entity::isActive() const noexcept { return active; }

void Entity::destroy() { active = false; }

bool Entity::hasGroup(Group mGroup) { return groupBitset[mGroup]; }

void Entity::addGroup(Group mGroup) {
  groupBitset[mGroup] = true;
  manager.AddToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) { groupBitset[mGroup] = false; }

size_t Entity::componentCount() { return components.size(); }

void Manager::update() {
  for (auto &e : entities)
    e->update();
}

void Manager::draw() {
  for (auto &e : entities)
    e->draw();
}

void Manager::refresh() {
  for (auto i(0u); i < maxGroups; i++) {
    auto &v(groupedEntities[i]);
    std::erase_if(v, [i](Entity *mEntity) {
      return !mEntity->isActive() || !mEntity->hasGroup(i);
    });
  }

  std::erase_if(entities, [](const std::unique_ptr<Entity> &mEntity) {
    return !mEntity->isActive();
  });
}

void Manager::AddToGroup(Entity *mEntity, Group mGroup) {
  groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity *> &Manager::getGroup(Group mGroup) {
  return groupedEntities[mGroup];
}

Entity &Manager::addEntity() {
  std::unique_ptr<Entity> entity = std::make_unique<Entity>(*this);
  Entity &ref = *entity;
  entities.emplace_back(std::move(entity));
  return ref;
}