#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <mutex>

#include "globals.h"
#include "utils/assetClasses.h"

namespace assets {
  extern sf::Font *mainFont; 
  
  extern SpriteSheet *spriteSheets[3];

  static int loadFonts() { // Self explanatory. return 0 means it passed.
    std::mutex mtx;
    mtx.lock();
    mainFont = new sf::Font();
    if (!mainFont->loadFromFile("assets/fonts/PixelFJVerdana12pt.ttf")) {
      return -1;
    }

    mtx.unlock();
    return 0;
  }

  static int loadTextures() { // Self explanatory. return 0 means it passed.
    std::mutex mtx;
    mtx.lock();

    for (unsigned int i = 0; i < 3; i++) {
      spriteSheets[i] = new SpriteSheet(i);
    }
    
    mtx.unlock();
    return 0;
  }
}
