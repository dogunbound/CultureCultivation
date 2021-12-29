#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>

#include "globals.h"
#include "utils/assetClasses.h"

namespace assets {
  extern sf::Font *mainFont; 

  extern SpriteSheet *autumnGrass; // Autumn grass sprite sheet

  // TREES ***************************************************************** TREES
  extern SpriteSheet *tree_autumnRedLeaves;


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
    
    autumnGrass = new SpriteSheet("assets/_tmp/autumnGrass2.png", 32);
    tree_autumnRedLeaves = new SpriteSheet("assets/entities/trees/autumnTree1.png", 32);
    
    mtx.unlock();
    return 0;
  }
}
