//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Core engine class.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_ENGINE_H_
#define FASTENGINE_ENGINE_H_

#include <array>

#include "../config.h"
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"

namespace fast_engine {

class Engine {
public:
  static Engine *getInstance() {
    return engineInstance =
               (engineInstance == nullptr ? new Engine() : engineInstance);
  }

  bool init();
  bool cleanup();

  void update();
  void render();
  void events();

  inline bool isRunning() { return this->isRunning_; }
  inline void setDrawColor(int r, int g, int b, int a = 255) {
    rendererDrawColor[0] = r;
    rendererDrawColor[1] = g;
    rendererDrawColor[2] = b;
    rendererDrawColor[3] = a;
    SDL_SetRenderDrawColor(renderer, rendererDrawColor[0], rendererDrawColor[1],
                           rendererDrawColor[2], rendererDrawColor[3]);
  }
  inline SDL_Window *getWindow() { return this->window; }
  inline SDL_Renderer *getRenderer() { return this->renderer; }

private:
  Engine() : rendererDrawColor(fe_config::DEFAULT_RENDERER_DRAW_COLOR) {}
  static Engine *engineInstance;

  // Core
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning_;

  // Misc
  std::array<int, 4> rendererDrawColor;
};

} // namespace fast_engine
#endif
