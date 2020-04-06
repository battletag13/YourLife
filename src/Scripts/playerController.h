//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Demo playerController header which allows the player to control a game
//  object.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef YOUR_LIFE_PLAYER_CONTROLLER_H_
#define YOUR_LIFE_PLAYER_CONTROLLER_H_

#include "engineAPI.h"

class PlayerController : public Component {
public:
  PlayerController(double speed, double diagonalMoveModifier)
      : speed(speed), diagonalMoveModifier(diagonalMoveModifier){};

  void update() {
    velocity = Vector2D(0, 0);
    if (input::getButton(SDLK_s)) {
      velocity.y = 1;
    } else if (input::getButton(SDLK_w)) {
      velocity.y = -1;
    }

    if (input::getButton(SDLK_a)) {
      velocity.x = -1;
    } else if (input::getButton(SDLK_d)) {
      velocity.x = 1;
    }

    if (velocity.x != 0 && velocity.y != 0) {
      velocity *= diagonalMoveModifier;
    }

    if (input::getButtonDown(SDLK_SPACE)) {
      gameObject->getComponent<Animator>().playAnimation("Wave");
    }
    if (input::getButtonDown(SDLK_v)) {
      gameObject->getComponent<Animator>().playAnimation("Peek");
    }
    if (input::getButtonDown(SDLK_b)) {
      GameObject &obj = gameObject->instantiate(
          gameObject->getComponent<Transform>().getPosition());
      obj.addComponent<SpritesheetRenderer>("src/Res/art.png", 0,
                                            Vector2D(8, 8))
          .setSprite(2);
      obj.getComponent<Transform>().scaleBy(Vector2D(10, 10));
    }
    if (input::getButtonDown(SDLK_n)) {
      GameObject &obj = gameObject->instantiate(
          gameObject->getComponent<Transform>().getPosition());
      obj.addComponent<SpritesheetRenderer>("src/Res/art.png", 2,
                                            Vector2D(8, 8))
          .setSprite(2);
      obj.getComponent<Transform>().scaleBy(Vector2D(10, 10));
    }

    gameObject->getComponent<Transform>().translate(time::deltaTime * velocity *
                                                    speed);
  }

  double speed;
  double diagonalMoveModifier;

private:
  int frame;
  Vector2D velocity;
};

#endif
