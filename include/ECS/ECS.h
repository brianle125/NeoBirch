#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

class Component;
class Entity;
class System;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

ComponentID getNewComponentTypeID();

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
  virtual ~Component();

  virtual void init();
  virtual void update();
  virtual void draw();
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
  Entity(Manager &mManager);

  void update();
  void draw();

  [[nodiscard]] bool isActive() const noexcept;
  void destroy();

  bool hasGroup(Group mGroup);

  void addGroup(Group mGroup);
  void delGroup(Group mGroup);

  template <typename T> 
  bool hasComponent() const {
    return componentBitset[getComponentTypeID<T>()];
  }

  size_t componentCount();

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
      std::erase_if(components, [](const std::unique_ptr<Component>& c) { 
        return c && dynamic_cast<T*>(c.get()) != nullptr; 
      });

      componentArray[id] = nullptr;
      componentBitset[id] = false;
    }
  }

  template <typename T> 
  T &getComponent() const {
    assert(hasComponent<T>());

    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }
};

class System {
  public:
    virtual void update(std::vector<Entity*>&) = 0;
};

class Manager {
private:
  std::vector<std::unique_ptr<Entity>> entities;
  std::array<std::vector<Entity *>, maxGroups> groupedEntities;

public:
  void update();
  void draw();
  void refresh();
  void AddToGroup(Entity *mEntity, Group mGroup);
  [[nodiscard]] std::vector<Entity *> &getGroup(Group mGroup);
  [[nodiscard]] Entity &addEntity();
};