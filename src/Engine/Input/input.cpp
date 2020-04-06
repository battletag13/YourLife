//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Input module implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include <map>

#include "SDL2/SDL.h"
#include "input.h"

namespace fast_engine {

Input *Input::inputInstance = nullptr;

Input::~Input() {
  if (event != nullptr) {
    delete event;
  }
}

void Input::handleCurrentEvent() {
  // State change only lasts for one frame
  mouseButtonStateChangeMap.reset();
  keyStateChangeMap.clear();

  // Update internal values based on inputs
  switch (event->type) {
  case SDL_KEYDOWN:
    keyMap[event->key.keysym.sym] = true;
    keyStateChangeMap[event->key.keysym.sym] = event->key.repeat ? false : true;
    keyStateChangeMapRepeatsCounted[event->key.keysym.sym] = true;
    break;
  case SDL_KEYUP:
    keyMap[event->key.keysym.sym] = false;
    keyStateChangeMap[event->key.keysym.sym] = event->key.repeat ? false : true;
    keyStateChangeMapRepeatsCounted[event->key.keysym.sym] = true;
    break;
  case SDL_MOUSEBUTTONDOWN:
    mouseButtonMap[event->button.button - 1] = true;
    mouseButtonStateChangeMap[event->button.button - 1] = true;
    break;
  case SDL_MOUSEBUTTONUP:
    mouseButtonMap[event->button.button - 1] = false;
    mouseButtonStateChangeMap[event->button.button - 1] = true;
    break;
  case SDL_MOUSEMOTION:
    break;
  case SDL_MOUSEWHEEL:
    break;
  default:
    break;
  }
}

bool Input::getMouseButtonDown(Uint8 buttonCode) {
  return mouseButtonMap[buttonCode] && mouseButtonStateChangeMap[buttonCode];
}
bool Input::getMouseButtonUp(Uint8 buttonCode) {
  return !mouseButtonMap[buttonCode] && mouseButtonStateChangeMap[buttonCode];
}
bool Input::getMouseButton(Uint8 buttonCode) {
  return mouseButtonMap[buttonCode];
}
bool Input::getButtonDown(SDL_Keycode keyCode, bool ignoreRepeats) {
  // Checking for state change
  auto iter = keyMap.find(keyCode);
  auto iter2 = keyStateChangeMap.find(keyCode);
  auto iter3 = keyStateChangeMapRepeatsCounted.find(keyCode);

  // Since we're checking for state change, no change also means false
  if (iter == keyMap.end() || iter2 == keyStateChangeMap.end()) {
    return false;
  } else {
    return iter->second && (ignoreRepeats ? iter2->second : iter3->second);
  }
}
bool Input::getButtonUp(SDL_Keycode keyCode) {
  // Checking for state change
  auto iter = keyMap.find(keyCode);
  auto iter2 = keyStateChangeMap.find(keyCode);

  // Since we're checking for state change, no change also means false
  if (iter == keyMap.end() || iter2 == keyStateChangeMap.end()) {
    return false;
  } else {
    return !iter->second && iter2->second;
  }
}
bool Input::getButton(SDL_Keycode keyCode) {
  // Here we are just checking for if the key is currently pressed
  auto iter = keyMap.find(keyCode);

  if (iter == keyMap.end()) {
    return false;
  } else {
    return iter->second;
  }
}

} // namespace fast_engine
