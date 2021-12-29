#include "assetClasses.h"

#include <iostream>

namespace assets {
  SpriteSheet::SpriteSheet(char const* pathToFile, unsigned int sizeOfEachSprite) : sizeOfEachSprite{sizeOfEachSprite}, texture{sf::Texture()} {
    if (!texture.loadFromFile(pathToFile)) {
      std::cout << "Failed to load texture: " << pathToFile << "\n";
      exit(-1);
    }

    texture.setSmooth(false);
  }

  sf::Rect<int> SpriteSheet::getSpriteRectAtIndex(const unsigned short& index) {
    if (index >= this->numOfSprites()) {
      std::cout << "invalid texture index\n";
      return sf::Rect<int>(0,0,0,0);
    }

    const unsigned int indexBySpriteSize = index * sizeOfEachSprite;
    return sf::Rect<int>(indexBySpriteSize, 
        0, 
        sizeOfEachSprite,
        texture.getSize().y);
  }

  unsigned int SpriteSheet::numOfSprites() { return texture.getSize().x / sizeOfEachSprite; }
}
