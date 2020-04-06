//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Transform implementation
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "transform.h"
#include "animation.h"

void fast_engine::Transform::setPosition(Vector2D position) {
  if (gameObject->hasComponent<Animator>()) {
    gameObject->getComponent<Animator>().updatePosition(position -
                                                        this->position);
  }
  this->position = position;
}

void fast_engine::Transform::setScale(Vector2D scale) {
  if (gameObject->hasComponent<Animator>()) {
    gameObject->getComponent<Animator>().updateScale(scale / this->scale);
  }
  this->scale = scale;
}

void fast_engine::Transform::setAngleOfRotation(double angleOfRotation) {
  if (gameObject->hasComponent<Animator>()) {
    gameObject->getComponent<Animator>().updateRotationAngle(
        angleOfRotation - this->angleOfRotation);
  }
  this->angleOfRotation = angleOfRotation;
}

void fast_engine::Transform::setPositionDiscrete(Vector2D position) {
  this->position = position;
}

void fast_engine::Transform::setScaleDiscrete(Vector2D scale) {
  this->scale = scale;
}

void fast_engine::Transform::setAngleOfRotationDiscrete(
    double angleOfRotation) {
  this->angleOfRotation = angleOfRotation;
}
