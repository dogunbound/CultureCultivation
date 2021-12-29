#pragma once

#include <SFML/Graphics.hpp>

namespace assets {
  class SpriteSheet {
    public:
      sf::Texture texture;
      const unsigned int sizeOfEachSprite;
      SpriteSheet(char const* pathToFile, unsigned int sizeOfEachSprite);

      // Gets the rect at a specified animation / index according to the size of
      sf::Rect<int> getSpriteRectAtIndex(const unsigned short& index);

      // Gets the number of indeces in the sprite sheet
      unsigned int numOfSprites();
  };
}
