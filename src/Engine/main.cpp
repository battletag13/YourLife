//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  A simple game engine written in C++ using SDL.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "../Scripts/start.h"
#include "Core/engine.h"
#include "SDL2/SDL.h"
#include "Utility/time.h"

int main() {
  fast_engine::Engine::getInstance()->init();

  start();

  int fps = fe_config::MAX_FPS;
  int frameDelay = 1000 / fps;

  // Start the frame clock
  MilisecondsTimer frameClock;

  while (fast_engine::Engine::getInstance()->isRunning()) {
    if (fps != fe_config::MAX_FPS) {
      fps = fe_config::MAX_FPS;
      frameDelay = 1000 / fps;
    }
    fast_engine::Engine::getInstance()->events();
    fast_engine::Engine::getInstance()->update();
    fast_engine::Engine::getInstance()->render();
    time::deltaTime = frameClock.reset();
    if (frameDelay > time::deltaTime) {
      SDL_Delay(frameDelay - time::deltaTime);
    }
  }

  fast_engine::Engine::getInstance()->cleanup();
}
