//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  The animation module holds various functions and classes to help with
//  sprite animation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_ANIMATOR_COMPONENT_H_
#define FASTENGINE_ANIMATOR_COMPONENT_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Logger/logger.h"
#include "../Utility/time.h"
#include "../Utility/vector2D.h"
#include "ecs.h"
#include "spritesheet_renderer.h"

namespace fast_engine {

namespace animation {
struct Keyframe {
  Keyframe(double durationMS)
      : visual(true), frameNumber(-1), durationMS(durationMS) {}
  Keyframe(double durationMS, int frameNumber)
      : visual(true), frameNumber(frameNumber), durationMS(durationMS) {}
  Keyframe(double durationMS, double rotationAngle, Vector2D position,
           Vector2D scale)
      : visual(false), durationMS(durationMS), rotationAngle(rotationAngle),
        position(position), scale(scale) {}

  bool visual;
  int frameNumber;
  double durationMS;
  double rotationAngle;
  Vector2D position;
  Vector2D scale;
};

class Animation {
public:
  Animation(const char *name, Transform *transform, bool looping = false,
            bool visual = false)
      : currentKeyframe(0), looping(looping), playing(false), visual(visual),
        name(std::string(name)), transform(transform) {
    updateSpritesheetRenderer();
  }

  // Animation editing
  void pushVisualFrame(int frame, double durationMS) {
    // Adding a visual keyframe
    keyframes.push_back(Keyframe(durationMS, frame));
  }
  void pushStateChangeFrame(double durationMS, double rotationAngle,
                            Vector2D position, Vector2D scale) {
    // Adding state change keyframe
    keyframes.push_back(Keyframe(durationMS, rotationAngle, position, scale));
  }
  void pushWaitFrame(double durationMS) {
    // Adding a wait keyframe
    keyframes.push_back(durationMS);
  }

  void update() {
    if (playing && keyframes.size() > 0) {

      // Interpolate between the next frame which may be state/visual frame
      Keyframe &keyframe = keyframes[currentKeyframe];
      double left = keyframe.durationMS - timer.count();
      if (left <= 0) {
        // Make sure any remaining interpolation is just snapped to place and
        // then move to the next keyframe
        if (!keyframe.visual) {
          lastPosition = lastPosition + keyframe.position;
          transform->setPositionDiscrete(lastPosition);

          lastScale = lastScale * keyframe.scale;
          transform->setScaleDiscrete(lastScale);

          lastRotationAngle = lastRotationAngle + keyframe.rotationAngle;
          transform->setAngleOfRotationDiscrete(lastRotationAngle);
        }
        if (++currentKeyframe >= keyframes.size()) {
          // We are done with this iteration
          if (looping)
            restart();
          else {
            pause();
          }
        }
        frameFinished = false;
        timer.reset();

        // If durationMS is 0, we must still change the sprite
        if (keyframe.durationMS != 0 || !keyframe.visual)
          return;
      }

      // Update sprite if necessary
      if (keyframe.visual && keyframe.frameNumber != -1 && !frameFinished) {
        frameFinished = true;
        spritesheetRenderer->setSprite(keyframe.frameNumber);
      }
      // Update state
      if (!keyframe.visual) {
        transform->setPositionDiscrete(lastPosition +
                                       keyframe.position *
                                           (1 - left / keyframe.durationMS));
        transform->setScaleDiscrete(lastScale +
                                    (keyframe.scale * lastScale - lastScale) *
                                        (1 - left / keyframe.durationMS));
        transform->setAngleOfRotationDiscrete(
            lastRotationAngle +
            keyframe.rotationAngle * (1 - left / keyframe.durationMS));
      }
    }
  }

  void setLooping(bool looping) { this->looping = looping; }
  void setVisual(bool visual) { this->visual = visual; }

  void updateSpritesheetRenderer() {
    spritesheetRenderer =
        &transform->gameObject->getComponent<SpritesheetRenderer>();
  }

  // Animation display

  // Reset animation
  void cancel() {
    timer.reset();
    playing = false;
  }
  // Start animation
  void play() {
    timer.start();
    playing = true;
    currentKeyframe = 0;
    lastPosition = startPosition = transform->getPosition();
    lastScale = startScale = transform->getScale();
    lastRotationAngle = startRotationAngle = transform->getAngleOfRotation();
    frameFinished = false;
  }
  // Stop animation
  void pause() {
    timer.stop();
    playing = false;
  }
  // Reset animation then start playing again
  void restart() {
    if (visual) {
      lastPosition = startPosition;
      lastScale = startScale;
      lastRotationAngle = startRotationAngle;

      transform->setPositionDiscrete(lastPosition);
      transform->setScaleDiscrete(lastScale);
      transform->setAngleOfRotationDiscrete(lastRotationAngle);
    }
    timer.reset();
    play();
  }

  void updatePosition(Vector2D positionChange) {
    startPosition += positionChange;
    lastPosition += positionChange;
  }
  void updateScale(Vector2D scaleMultiplier) {
    startScale *= scaleMultiplier;
    lastScale *= scaleMultiplier;
  }
  void updateRotationAngle(double rotationAngleChange) {
    startRotationAngle += rotationAngleChange;
    lastRotationAngle += rotationAngleChange;
  }

  std::string &getName() { return name; }
  bool isPlaying() { return playing; }

private:
  double duration;
  int currentKeyframe;
  bool looping;
  bool playing;
  bool frameFinished;
  bool visual;

  std::string name;
  std::vector<Keyframe> keyframes;

  MilisecondsTimer timer;
  Transform *transform;
  SpritesheetRenderer *spritesheetRenderer;

  double lastRotationAngle, startRotationAngle;
  Vector2D lastPosition, startPosition;
  Vector2D lastScale, startScale;
};
} // namespace animation

class Animator : public Component {
public:
  Animator()
      : spritesheetRenderer(nullptr), currentlyPlayingAnimation(nullptr) {}
  virtual void start() override { checkRenderer(); }
  virtual void update() override {
    if (currentlyPlayingAnimation != nullptr)
      currentlyPlayingAnimation->update();
  }

  // Checks if a SpritesheetRenderer exists and adds it if possible
  void checkRenderer() {
    if (!gameObject->hasComponent<SpritesheetRenderer>()) {
      Logger::getInstance()->logWarning(
          "Animator created with no existing spritesheet renderer!\nCall "
          "checkRenderer to attempt to fix the issue.");
    } else {
      spritesheetRenderer = &gameObject->getComponent<SpritesheetRenderer>();
      for (auto animation : animations) {
        animation.second->updateSpritesheetRenderer();
      }
    }
  }
  // Updates any transform changes since animation start
  void updatePosition(Vector2D positionChange) {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->updatePosition(positionChange);
    }
  }
  void updateScale(Vector2D scaleMultiplier) {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->updateScale(scaleMultiplier);
    }
  }
  void updateRotationAngle(double rotationAngleChange) {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->updateRotationAngle(rotationAngleChange);
    }
  }

  // Animation control
  void playAnimation(const char *name) {
    std::string animationName(name);
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->cancel();
    }
    // Play animation if possible
    auto animationIter = animations.find(animationName);
    if (animationIter != animations.end()) {
      currentlyPlayingAnimation = &(*animationIter->second);
      currentlyPlayingAnimation->play();
      currentlyPlayingAnimation->restart();
    } else {
      Logger::getInstance()->logWarning("Animation of name " + animationName +
                                        " not found!");
    }
  }
  void pauseAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->pause();
    } else {
      Logger::getInstance()->logWarning("No animation currently playing!");
    }
  }
  void resumeAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->play();
    } else {
      Logger::getInstance()->logWarning("No animation currently paused!");
    }
  }
  void cancelAnimation() {
    if (currentlyPlayingAnimation != nullptr) {
      currentlyPlayingAnimation->cancel();
      currentlyPlayingAnimation = nullptr;
    } else {
      Logger::getInstance()->logWarning("No animation currently playing!");
    }
  }

  // Creates a blank animation
  animation::Animation &createAnimation(const char *name, bool looping = false,
                                        bool visual = false) {
    std::string animationName = std::string(name);
    animation::Animation *animation = new animation::Animation(
        name, &gameObject->getComponent<Transform>(), looping, visual);
    std::shared_ptr<animation::Animation> animationUPtr{animation};
    animations.insert(std::make_pair(animationName, std::move(animationUPtr)));
    return *animations.at(animationName);
  }
  // Creates an animation with a count and startSprite
  animation::Animation &createStillAnimation(const char *name, int count,
                                             double duration,
                                             int startSprite = 0,
                                             bool looping = false,
                                             bool visual = false) {
    std::string animationName = std::string(name);
    animation::Animation *animation = new animation::Animation(
        name, &gameObject->getComponent<Transform>(), looping, visual);

    double eachDuration = duration / count;
    for (int i = 0; i < count; ++i) {
      animation->pushVisualFrame(startSprite + i, eachDuration);
    }

    std::shared_ptr<animation::Animation> animationUPtr{animation};
    animations.insert(std::make_pair(animationName, std::move(animationUPtr)));
    return *animations.at(animationName);
  }

private:
  SpritesheetRenderer *spritesheetRenderer;
  animation::Animation *currentlyPlayingAnimation;
  std::unordered_map<std::string, std::shared_ptr<animation::Animation>>
      animations;
};

} // namespace fast_engine

#endif
