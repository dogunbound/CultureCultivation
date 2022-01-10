#include "assetClasses.h"
#include "assets.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace assets {
  // SPRITE SHEET ************************************************
  SpriteSheet::SpriteSheet(const unsigned int &id) : 
    sizeOfEachSprite{SpriteSheetDataID[id].sizeOfEachSprite}, 
    texture{sf::Texture()} {
    if (!texture.loadFromFile(SpriteSheetDataID[id].pathToFile)) {
      std::cout << "Failed to load texture: " << SpriteSheetDataID[id].pathToFile << "\n";
      exit(-1);
    }

    texture.setSmooth(false);
  }

  sf::Rect<int> SpriteSheet::getSpriteRectAtIndex(const unsigned short& index) {
    if (index >= this->numOfSprites()) {
      std::cout << "invalid texture index\n";
      return sf::Rect<int>(0,0,sizeOfEachSprite,texture.getSize().y);
    }

    const unsigned int indexBySpriteSize = index * sizeOfEachSprite;
    return sf::Rect<int>(indexBySpriteSize, 
        0, 
        sizeOfEachSprite,
        texture.getSize().y);
  }

  const unsigned int SpriteSheet::numOfSprites() const { return texture.getSize().x / sizeOfEachSprite; }
}
