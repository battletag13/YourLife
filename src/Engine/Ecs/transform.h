//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Transform is one of the core components of the ECS.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_TRANSFORM_COMPONENT_H_
#define FASTENGINE_TRANSFORM_COMPONENT_H_

#include <cmath>

#include "../Utility/vector2D.h"
#include "ecs.h"

namespace fast_engine {

class Transform : public Component {
public:
  Transform()
      : position(0, 0), scale(1, 1), angleOfRotation(0),
        baseRenderedSize(0, 0) {}

  // Basic transform operations
  void translate(Vector2D vector) { setPosition(position + vector); }
  void rotate(double angle) {
    setAngleOfRotation(angleOfRotation + angle);
    if (angleOfRotation < 0) {
      angleOfRotation = -angleOfRotation;
      angleOfRotation = std::fmod(angleOfRotation, 360);
      setAngleOfRotation(-angleOfRotation);
    } else {
      setAngleOfRotation(std::fmod(angleOfRotation, 360));
    }
  }

  void scaleBy(Vector2D scalar) { setScale(scale * scalar); }

  Vector2D getPosition() { return position; }
  void setPosition(Vector2D position);
  void setPositionDiscrete(Vector2D position);

  Vector2D getScale() { return scale; }
  void setScale(Vector2D scale);
  void setScaleDiscrete(Vector2D scale);

  // Size of srcRect
  Vector2D getBaseRenderedSize() { return baseRenderedSize; }
  void setBaseRenderedSize(Vector2D baseRenderedSize) {
    this->baseRenderedSize = baseRenderedSize;
  }

  // Final render size (what is seen on screen)
  Vector2D getFinalRenderedSize() { return baseRenderedSize * scale; }

  double getAngleOfRotation() { return angleOfRotation; }
  void setAngleOfRotation(double angleOfRotation);
  void setAngleOfRotationDiscrete(double angleOfRotation);

private:
  // Members
  Vector2D position;
  Vector2D scale;
  Vector2D baseRenderedSize;
  double angleOfRotation;
};

} // namespace fast_engine
#endif
