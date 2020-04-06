//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  This input uses the internal input module to give input checking access to
//  the user.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_UTIL_INPUT_H_
#define FASTENGINE_UTIL_INPUT_H_

#include "../Input/input.h"

namespace input {

SDL_Event *getCurrentEvent() {
  return fast_engine::Input::getInstance()->getCurrentEvent();
}

bool getMouseButtonDown(Uint8 buttonCode) {
  return fast_engine::Input::getInstance()->getMouseButtonDown(buttonCode);
}
bool getMouseButtonUp(Uint8 buttonCode) {
  return fast_engine::Input::getInstance()->getMouseButtonUp(buttonCode);
}
bool getMouseButton(Uint8 buttonCode) {
  return fast_engine::Input::getInstance()->getMouseButton(buttonCode);
}
bool getButtonDown(SDL_Keycode keyCode, bool ignoreRepeats = true) {
  return fast_engine::Input::getInstance()->getButtonDown(keyCode,
                                                          ignoreRepeats);
}
bool getButtonUp(SDL_Keycode keyCode) {
  return fast_engine::Input::getInstance()->getButtonUp(keyCode);
}
bool getButton(SDL_Keycode keyCode) {
  return fast_engine::Input::getInstance()->getButton(keyCode);
}

} // namespace input

#endif
