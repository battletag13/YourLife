//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Texture manager implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include <map>
#include <vector>

#include "../Core/engine.h"
#include "../Logger/logger.h"
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"
#include "texture_manager.h"

namespace fast_engine {

TextureManager *TextureManager::textureManagerInstance = nullptr;

void TextureManager::render(SDL_Texture *texture, SDL_Rect srcRect,
                            SDL_Rect destRect, const double rotationAngle) {
  SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), texture, &srcRect,
                   &destRect, rotationAngle, NULL, SDL_FLIP_NONE);
}

void TextureManager::renderQueue(SDL_Texture *texture, SDL_Rect srcRect,
                                 SDL_Rect destRect, int sortingOrder,
                                 const double rotationAngle) {
  if (renderMap.find(sortingOrder) == renderMap.end())
    renderMap.insert(std::make_pair(
        sortingOrder, std::vector<RenderData>{RenderData(
                          texture, srcRect, destRect, rotationAngle)}));
  else {
    renderMap.find(sortingOrder)
        ->second.push_back(
            RenderData(texture, srcRect, destRect, rotationAngle));
  }
}

void TextureManager::renderAll() {
  std::map<int, std::vector<RenderData>>::iterator it = renderMap.begin();
  while (it != renderMap.end()) {
    std::vector<RenderData> dataVector = it++->second;
    for (auto data : dataVector)
      render(data.texture, data.srcRect, data.destRect, data.rotationAngle);
  }
  renderMap.clear();
}

SDL_Texture *TextureManager::loadTexture(const std::string pathToTexture) {
  SDL_Surface *tempSurface = IMG_Load(pathToTexture.c_str());
  if (tempSurface == nullptr) {
    Logger::getInstance()->logError("Failed to load texture!");
    Logger::getInstance()->logError(IMG_GetError());
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      Engine::getInstance()->getRenderer(), tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}

SDL_Surface *TextureManager::loadSurface(const std::string pathToSurface) {
  SDL_Surface *surface = IMG_Load(pathToSurface.c_str());
  if (surface == nullptr) {
    Logger::getInstance()->logError("Failed to load surface!");
    Logger::getInstance()->logError(IMG_GetError());
  }

  return surface;
}

} // namespace fast_engine
