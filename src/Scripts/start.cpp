//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  This is the entrypoint for any games created with FastEngine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//

// Core includes
#include "start.h"
#include "engineAPI.h"

// Other includes
#include "playerController.h"

// Used for addGameObject
Manager *manager = Manager::getInstance();

void start() {
  // Game starts here!
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);

  setWindowProperties("Your Life", true, Vector2D(DM.w, DM.h));

  GameObject &player = manager->addGameObject();
  player.addComponent<SpritesheetRenderer>("src/Res/playerss.png", 1,
                                           Vector2D(8, 8));
  player.getComponent<SpritesheetRenderer>().setSprite(0);
  player.addComponent<PlayerController>(1, 0.7);
  player.getComponent<Transform>().scaleBy(Vector2D(10, 10));

  player.addComponent<Animator>();
  Animation &wave =
      player.getComponent<Animator>().createAnimation("Wave", false, true);
  wave.pushVisualFrame(3, 100);
  wave.pushVisualFrame(4, 100);
  wave.pushVisualFrame(3, 100);
  wave.pushVisualFrame(4, 100);
  wave.pushVisualFrame(0, 0);

  Animation &peek =
      player.getComponent<Animator>().createAnimation("Peek", false, false);
  peek.pushVisualFrame(6, 0);
  peek.pushStateChangeFrame(0, 0, Vector2D(0, -30), Vector2D(1, 1));
  peek.pushWaitFrame(1000);
  peek.pushStateChangeFrame(0, 0, Vector2D(0, -10), Vector2D(1, 1));
  peek.pushWaitFrame(1000);
  peek.pushStateChangeFrame(0, 0, Vector2D(0, 40), Vector2D(1, 1));
  peek.pushVisualFrame(0, 0);
}
