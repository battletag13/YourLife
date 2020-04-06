//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Constants required by the engine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_CONSTANTS_H_
#define FASTENGINE_CONSTANTS_H_

#include <array>
#include <string>

#include "Utility/vector2D.h"

namespace fe_config {

// Core config
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int MAX_FPS;
extern std::string WINDOW_TITLE;

// ECS config
extern Vector2D SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE;

extern Vector2D SPRITESHEET_RENDERER_DEFAULT_OFFSET_SIZE;
extern Vector2D SPRITESHEET_RENDERER_DEFAULT_PADDING_SIZE;

// Core constants
constexpr std::array<int, 4> DEFAULT_RENDERER_DRAW_COLOR = {104, 130, 158, 255};

// ECS constants
constexpr int MAX_COMPONENTS = 512;

// Logger constants
constexpr const char *DEFAULT_ERROR_MESSAGE = "An unknown error has occured!";
constexpr const char *LOG_FILE = "log.txt";
constexpr bool LOGGING_TO_FILE = false;

} // namespace fe_config

#endif
