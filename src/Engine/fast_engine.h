//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  This is the header to include in order to configure/interface with the
//  engine
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_FAST_ENGINE_H_
#define FASTENGINE_FAST_ENGINE_H_

#include <string>

#include "config.h"

// Core includes
#include "Core/engine.h"

// ECS includes
#include "Ecs/animation.h"
#include "Ecs/ecs.h"
#include "Ecs/sprite_renderer.h"
#include "Ecs/spritesheet_renderer.h"
#include "Ecs/transform.h"

// Utility includes
#include "Utility/time.h"
#include "Utility/util_input.h"
#include "Utility/util_logger.h"
#include "Utility/vector2D.h"

// SDL includes
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"

// Engine configuration

using fast_engine::Animator;
using fast_engine::Component;
using fast_engine::GameObject;
using fast_engine::Manager;
using fast_engine::SpriteRenderer;
using fast_engine::SpritesheetRenderer;
using fast_engine::Transform;
using fast_engine::animation::Animation;

// Core configuration
void setMaxFps(int FPS) { fe_config::MAX_FPS = FPS; }

// Sets background color of the window
void setBackgroundColor(int r, int g, int b, int a = 255) {
  fast_engine::Engine::getInstance()->setDrawColor(r, g, b, a);
};

// Window functions
Vector2D getScreenDimensions() {
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);

  return Vector2D(DM.w, DM.h);
}
SDL_DisplayMode getDisplayPropertites() {
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);

  return DM;
}
void setWindowProperties(std::string windowTitle, bool fullscreen = false,
                         Vector2D size = Vector2D(fe_config::WINDOW_WIDTH,
                                                  fe_config::WINDOW_HEIGHT)) {
  fe_config::WINDOW_WIDTH = size.x;
  fe_config::WINDOW_HEIGHT = size.y;
  fe_config::WINDOW_TITLE = windowTitle;

  SDL_SetWindowTitle(fast_engine::Engine::getInstance()->getWindow(),
                     windowTitle.c_str());
  SDL_SetWindowSize(fast_engine::Engine::getInstance()->getWindow(), size.x,
                    size.y);
  SDL_SetWindowFullscreen(fast_engine::Engine::getInstance()->getWindow(),
                          (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
}

// Sprite renderer defaults
void setSpriteRendererDefaultSrcRectSize(Vector2D size) {
  fe_config::SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE = size;
}
void setSpriteRendererDefaultOffsetSize(Vector2D size) {
  fe_config::SPRITESHEET_RENDERER_DEFAULT_OFFSET_SIZE = size;
}
void setSpriteRendererDefaultPaddingSize(Vector2D size) {
  fe_config::SPRITESHEET_RENDERER_DEFAULT_PADDING_SIZE = size;
}

#endif
