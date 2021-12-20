#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>

#include "globals.h"
#include "utils/assetClasses.h"

namespace assets {
  extern sf::Font *mainFont; 

  extern sf::Texture *grass; // Temporary

  extern SpriteSheet *autumnGrass; // Autumn grass sprite sheet


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
    grass = new sf::Texture();
    if (!grass->loadFromFile("assets/_tmp/grass.png")) {
      return -1;
    }

    autumnGrass = new SpriteSheet("assets/_tmp/autumnGrass_1_2_3_4.png", 16);
    
    mtx.unlock();
    return 0;
  }
}
