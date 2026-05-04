#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
  static ComponentID lastID = 0u;
  return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
  static_assert(std::is_base_of<Component, T>::value, "");
  static ComponentID typeID = getNewComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
  Entity *entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}
  virtual ~Component() {}
};

class Entity {
private:
  Manager &manager;
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitset;
  GroupBitset groupBitset;

public:
  Entity(Manager &mManager) : manager(mManager) {}

  void update() {
    for (auto &c : components)
      c->update();
  }
  void draw() {
    for (auto &c : components)
      c->draw();
  }

  [[nodiscard]] bool isActive() const noexcept { return active; }
  void destroy() { active = false; }

  bool hasGroup(Group mGroup) { return groupBitset[mGroup]; }

  void addGroup(Group mGroup);
  void delGroup(Group mGroup) { groupBitset[mGroup] = false; }

  template <typename T> 
  bool hasComponent() const {
    return componentBitset[getComponentTypeID<T>()];
  }

  // Add a component to the entity.
  template <typename T, typename... TArgs> 
  T &addComponent(TArgs &&...mArgs) {
    auto component = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
    component->entity = this;

    T &ref = *component;
    componentArray[getComponentTypeID<T>()] = component.get();
    componentBitset[getComponentTypeID<T>()] = true;

    components.emplace_back(std::move(component));
    ref.init();
    return ref;
  }

  // Removes a component from the entity.
  template <typename T> 
  void removeComponent() {
    ComponentID id = getComponentTypeID<T>();

    if (componentBitset[id]) {
      std::erase_if(components, [id](const std::unique_ptr<Component>& c) { 
        return getComponentTypeID<T>() == id; 
      });

      componentArray[id] = nullptr;
      componentBitset[id] = false;
    }
  }

  template <typename T> 
  T &getComponent() const {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }
};

class Manager {
private:
  std::vector<std::unique_ptr<Entity>> entities;
  std::array<std::vector<Entity *>, maxGroups> groupedEntities;

public:
  void update() {
    for (auto &e : entities)
      e->update();
  }
  void draw() {
    for (auto &e : entities)
      e->draw();
  }
  void refresh() {
    for (auto i(0u); i < maxGroups; i++) {
      auto &v(groupedEntities[i]);
      std::erase_if(v, [i](Entity* mEntity) {
        return !mEntity->isActive() || !mEntity->hasGroup(i);
      });

      // pre c++20
      // v.erase(std::remove_if(std::begin(v), std::end(v),
      //                        [i](Entity *mEntity) {
      //                          return !mEntity->isActive() ||
      //                                 !mEntity->hasGroup(i);
      //                        }),
      //         std::end(v));
    }

    std::erase_if(entities, [](const std::unique_ptr<Entity>& mEntity) {
    return !mEntity->isActive(); });
  }

  void AddToGroup(Entity *mEntity, Group mGroup) {
    groupedEntities[mGroup].emplace_back(mEntity);
  }

  [[nodiscard]] std::vector<Entity *> &getGroup(Group mGroup) {
    return groupedEntities[mGroup];
  }

  [[nodiscard]] Entity &addEntity() {
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(*this);
    Entity &ref = *entity; // keep reference before moving
    entities.emplace_back(std::move(entity));
    return ref;
  }
};