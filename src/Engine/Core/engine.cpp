//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Core engine implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "engine.h"
#include "../Ecs/ecs.h"
#include "../Graphics/texture_manager.h"
#include "../Input/input.h"
#include "../Logger/logger.h"
#include "../config.h"

namespace fast_engine {

Engine *Engine::engineInstance = nullptr;

bool Engine::init() {
  int SDL_ImageFlags = (IMG_INIT_JPG | IMG_INIT_PNG);

  // Make sure SDL and SDL_Image both initialize properly
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ||
      !(IMG_Init(SDL_ImageFlags) & SDL_ImageFlags)) {
    Logger::getInstance()->logError("Failed to initialize SDL!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  Logger::getInstance()->log("SDL initialized!");

  // Create our window and check for errors
  window =
      SDL_CreateWindow(fe_config::WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, fe_config::WINDOW_WIDTH,
                       fe_config::WINDOW_HEIGHT, 0);
  if (window == nullptr) {
    Logger::getInstance()->logError("Failed to create window!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  Logger::getInstance()->log("Window created!");

  // Create our renderer and check for errors
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    Logger::getInstance()->logError("Failed to create renderer!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(renderer, rendererDrawColor[0], rendererDrawColor[1],
                         rendererDrawColor[2], rendererDrawColor[3]);
  Logger::getInstance()->log("Renderer created!");

  Logger::getInstance()->log("Engine initialized!");
  return isRunning_ = true;
}
bool Engine::cleanup() {
  // SDL cleanup
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  IMG_Quit();
  SDL_Quit();
  // Clearing pointers
  delete this->getInstance();

  Logger::getInstance()->log("Engine cleaned!");

  delete Logger::getInstance();
  return true;
}

void Engine::update() {
  Manager::getInstance()->update();
  Manager::getInstance()->clean();
}
void Engine::render() {
  // Prepare the renderer
  SDL_RenderClear(renderer);

  Manager::getInstance()->render();
  TextureManager::getInstance()->renderAll();

  // Present the renderer
  SDL_RenderPresent(renderer);
}
void Engine::events() {
  if (SDL_PollEvent(Input::getInstance()->getCurrentEvent()) == 0)
    *Input::getInstance()->getCurrentEvent() = SDL_Event();
  if (Input::getInstance()->getCurrentEvent()->type == SDL_QUIT) {
    isRunning_ = false;
  }
  // Handoff duties to the Input class
  Input::getInstance()->handleCurrentEvent();
}

} // namespace fast_engine
