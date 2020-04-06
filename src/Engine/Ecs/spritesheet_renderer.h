//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  SpritesheetRenderer is one of the core components of the ECS.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_SPRITESHEET_RENDERER_COMPONENT_H_
#define FASTENGINE_SPRITESHEET_RENDERER_COMPONENT_H_

#include "../Graphics/texture_manager.h"
#include "../config.h"
#include "SDL2/SDL.h"
#include "ecs.h"
#include "transform.h"

namespace fast_engine {

class SpritesheetRenderer : public Component {
public:
  // Constructors
  SpritesheetRenderer(
      const std::string pathToSpritesheet, int sortingOrder = 0,
      Vector2D srcRectSize = fe_config::SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE,
      Vector2D offset = fe_config::SPRITESHEET_RENDERER_DEFAULT_OFFSET_SIZE,
      Vector2D padding = fe_config::SPRITESHEET_RENDERER_DEFAULT_PADDING_SIZE)
      : sortingOrder(sortingOrder), offset(offset), padding(padding) {

    setTexture(pathToSpritesheet);

    SDL_Surface *surface =
        TextureManager::getInstance()->loadSurface(pathToSpritesheet);

    srcRect.w = srcRectSize.x;
    srcRect.h = srcRectSize.y;
    srcRect.x = offset.x;
    srcRect.y = offset.y;

    spritesheetDimensions.x = surface->w;
    spritesheetDimensions.y = surface->h;

    spriteCount = 0;
    currentIndex = 0;
    for (int y = offset.y; y < spritesheetDimensions.y;
         y += srcRectSize.y + padding.y) {
      for (int x = offset.x; x < spritesheetDimensions.x;
           x += srcRectSize.x + padding.x) {
        // This is where we start counting tiles
        ++spriteCount;
      }
    }

    SDL_FreeSurface(surface);
  }
  ~SpritesheetRenderer() { SDL_DestroyTexture(objectTexture); }

  // Utility
  virtual void start() override {
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    gameObject->getComponent<Transform>().setBaseRenderedSize(
        Vector2D(srcRect.w, srcRect.h));
  }
  virtual void render() override {
    TextureManager::getInstance()->renderQueue(
        objectTexture, srcRect, destRect, sortingOrder,
        gameObject->getComponent<Transform>().getAngleOfRotation());
  }
  void setSrcRectSize(Vector2D srcRectSize) {
    srcRect.w = srcRectSize.x;
    srcRect.h = srcRectSize.y;
  }
  // Set the sprite this renderer is going to display
  void setSprite(int index) {
    currentIndex = 0;
    for (int y = offset.y; y < spritesheetDimensions.y;
         y += srcRect.w + padding.y) {
      for (int x = offset.x; x < spritesheetDimensions.x;
           x += srcRect.h + padding.x) {
        // This is where we start counting tiles
        if (currentIndex == index) {
          srcRect.x = x;
          srcRect.y = y;
          return;
        }
        ++currentIndex;
      }
    }
  }
  // Set the sprite this renderer is going to display to the next sprite
  void nextSprite() {
    if (++currentIndex >= spriteCount)
      currentIndex = 0;

    setSprite(currentIndex);
  }
  void setTexture(const std::string pathToTexture) {
    objectTexture = TextureManager::getInstance()->loadTexture(pathToTexture);
  }
  virtual void update() override {
    Transform &transform = gameObject->getComponent<Transform>();
    // Update position
    destRect.x = transform.getPosition().x;
    destRect.y = transform.getPosition().y;

    // Update scale
    destRect.w = srcRect.w * transform.getScale().x;
    destRect.h = srcRect.h * transform.getScale().y;
  }

  int getSortingOrder() { return sortingOrder; }
  void setSortingOrder(int sortingOrder) { this->sortingOrder = sortingOrder; }

  int spriteCount;
  int currentIndex;

private:
  int sortingOrder;

  SDL_Texture *objectTexture;
  SDL_Rect srcRect, destRect;

  Vector2D offset;
  Vector2D padding;
  Vector2D spritesheetDimensions;
};

} // namespace fast_engine
#endif
