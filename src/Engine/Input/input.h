//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Input module provides an interface for scripts to access input data.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_INPUT_H_
#define FASTENGINE_INPUT_H_

#include "SDL2/SDL.h"
#include <bitset>
#include <map>

namespace fast_engine {

class Input {
public:
  ~Input();

  static Input *getInstance() {
    return inputInstance =
               (inputInstance == nullptr ? new Input() : inputInstance);
  }

  SDL_Event *getCurrentEvent() {
    return event = (event == nullptr ? new SDL_Event() : event);
  }
  void handleCurrentEvent();

  // Input checking functions
  bool getMouseButtonDown(Uint8 buttonCode);
  bool getMouseButtonUp(Uint8 buttonCode);
  bool getMouseButton(Uint8 buttonCode);
  bool getButtonDown(SDL_Keycode keyCode, bool ignoreRepeats = true);
  bool getButtonUp(SDL_Keycode keyCode);
  bool getButton(SDL_Keycode keyCode);

private:
  Input() : event(nullptr){};
  static Input *inputInstance;

  SDL_Event *event;
  std::map<SDL_Keycode, bool> keyMap;
  std::map<SDL_Keycode, bool> keyStateChangeMap;
  std::map<SDL_Keycode, bool> keyStateChangeMapRepeatsCounted;
  std::bitset<3> mouseButtonMap;
  std::bitset<3> mouseButtonStateChangeMap;
};

} // namespace fast_engine
#endif
