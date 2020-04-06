//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Parts of ECS that couldn't be implemented in the header are implemented
//  here.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "ecs.h"
#include "transform.h"

namespace fast_engine {

Manager *Manager::managerInstance = nullptr;

GameObject &GameObject::instantiate(Vector2D position) {
  GameObject &object = manager->addGameObject();
  object.getComponent<Transform>().setPosition(position);
  return object;
}

GameObject &Manager::addGameObject() {
  GameObject *gameObject = new GameObject(this);
  std::unique_ptr<GameObject> gameObjectUPtr{gameObject};
  gameObjectsWaiting.emplace_back(std::move(gameObjectUPtr));

  gameObject->addComponent<Transform>();
  return *gameObject;
}

} // namespace fast_engine
