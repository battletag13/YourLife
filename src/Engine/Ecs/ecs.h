//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  The Entity Component System allows for the creation of custom components
//  into the game which serves at the core of this engine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_ECS_H_
#define FASTENGINE_ECS_H_

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdlib>
#include <memory>
#include <vector>

#include "../Utility/vector2D.h"
#include "../config.h"

namespace fast_engine {

// Core classes
struct Component;
class GameObject;
class Manager;
// Core components
class Transform;

// Will be used in the GameObject class for managing components
using ComponentArray = std::array<Component *, fe_config::MAX_COMPONENTS>;
using ComponentBitset = std::bitset<fe_config::MAX_COMPONENTS>;

// Allows each component type to have an unique identifier
inline std::size_t getComponentTypeID() {
  static std::size_t lastID = 0;
  return lastID++;
}
template <typename T> inline std::size_t getComponentTypeID() {
  static std::size_t typeID = getComponentTypeID();
  return typeID;
}

// Core of the ECS
struct Component {
  virtual ~Component(){};

  virtual void start(){};
  virtual void update(){};
  virtual void render(){};

  GameObject *gameObject;
};

// Game objects hold components
class GameObject {
public:
  GameObject(Manager *manager)
      : manager(manager), active(true), destroyed(false) {}

  inline bool isActive() { return active; }
  inline void setActive(bool activeState) { active = activeState; }

  inline bool isDestroyed() { return destroyed; }
  inline void destroy() {
    active = false;
    destroyed = true;
  }

  void update() {
    for (auto &component : components) {
      component->update();
    }
  }
  void render() {
    for (auto &component : components) {
      component->render();
    }
  }

  // Add a new component to this game object
  template <typename T, typename... TArgs> T &addComponent(TArgs &&... args) {
    T *componentPtr(new T(std::forward<TArgs>(args)...));
    componentPtr->gameObject = this;

    std::unique_ptr<Component> componentUPtr{componentPtr};
    components.emplace_back(std::move(componentUPtr));

    componentArray[getComponentTypeID<T>()] = componentPtr;
    componentBitset[getComponentTypeID<T>()] = true;

    componentPtr->start();
    return *componentPtr;
  }
  // Get a component from this game object
  template <typename T> T &getComponent() {
    auto componentPtr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(componentPtr);
  }
  template <typename T> inline bool hasComponent() {
    return componentBitset[getComponentTypeID<T>()];
  }
  // Instantiate a new GameObject
  GameObject &instantiate(Vector2D position);

private:
  bool active;
  bool destroyed;

  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitset componentBitset;
  Manager *manager;
};

// The manager holds all of the game objects
class Manager {
public:
  static Manager *getInstance() {
    return managerInstance =
               (managerInstance == nullptr ? new Manager() : managerInstance);
  }

  void update() {
    for (auto &gameObject : gameObjects) {
      gameObject->update();
    }
    while (gameObjectsWaiting.size() > 0) {
      std::vector<std::unique_ptr<GameObject>>::iterator it =
          gameObjectsWaiting.begin();
      gameObjects.push_back(std::move(*it));
      gameObjectsWaiting.erase(it);
    }
  }
  void render() {
    for (auto &gameObject : gameObjects) {
      gameObject->render();
    }
  }
  void clean() {
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
                       [](const std::unique_ptr<GameObject> &gameObject) {
                         return gameObject->isDestroyed();
                       }),
        gameObjects.end());
  }

  GameObject &addGameObject();

private:
  Manager() : gameObjects(), gameObjectsWaiting() {}
  static Manager *managerInstance;

  std::vector<std::unique_ptr<GameObject>> gameObjects;
  std::vector<std::unique_ptr<GameObject>> gameObjectsWaiting;
};

} // namespace fast_engine
#endif
