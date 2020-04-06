//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  The texture manager module manages the loading of graphics into our engine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_TEXTURE_MANAGER_H_
#define FASTENGINE_TEXTURE_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "SDL2/SDL.h"

namespace fast_engine {

struct RenderData {
  RenderData(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect,
             double rotationAngle)
      : texture(texture), srcRect(srcRect), destRect(destRect),
        rotationAngle(rotationAngle) {}

  SDL_Texture *texture;
  SDL_Rect srcRect;
  SDL_Rect destRect;
  double rotationAngle;
};

class TextureManager {
public:
  static TextureManager *getInstance() {
    return textureManagerInstance =
               (textureManagerInstance == nullptr ? new TextureManager()
                                                  : textureManagerInstance);
  }

  // General function for rendering an SDL Texture
  void render(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect,
              const double rotationAngle = 0);
  // Queue a render
  void renderQueue(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect,
                   int sortingOrder = 0, const double rotationAngle = 0);
  void renderAll();

  // For loading a texture from a file
  static SDL_Texture *loadTexture(const std::string pathToTexture);
  // For loading a surface from a file
  static SDL_Surface *loadSurface(const std::string pathToSurface);

private:
  TextureManager() : renderMap() {}
  static TextureManager *textureManagerInstance;

  std::map<int, std::vector<RenderData>> renderMap;
};

} // namespace fast_engine
#endif
