#pragma once

#include <SFML/Graphics.hpp>

namespace assets {
  struct SpriteSheetData {
    char const* name;
    char const* pathToFile;
    const unsigned int sizeOfEachSprite;
  };

  static const SpriteSheetData SpriteSheetDataID[3] = {
    { "missing texture", "assets/missing_texture.png", 32 },
    { "autumn grass 2", "assets/_tmp/autumnGrass2.png", 32 },
    { "autumn tree 1", "assets/entities/trees/autumnTree1.png", 32 }
  };

  class SpriteSheet {
    public:
      sf::Texture texture;
      const unsigned int sizeOfEachSprite;
      SpriteSheet(const unsigned int &id);

      // Gets the rect at a specified animation / index according to the size of
      sf::Rect<int> getSpriteRectAtIndex(const unsigned short& index);

      // Gets the number of indeces in the sprite sheet
      const unsigned int numOfSprites() const;
  };
}
