#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>

#include "globals.h"

namespace assets {
  static sf::Font mainFont;

  static sf::Texture grass;


  static int loadFonts() {
    std::mutex mtx;
    mtx.lock();
    if (!mainFont.loadFromFile("assets/fonts/PixelFJVerdana12pt.ttf")) {
      return -1;
    }

    mtx.unlock();
    return 0;
  }

  static int loadTextures() {
    std::mutex mtx;
    mtx.lock();
    if (!grass.loadFromFile("assets/_tmp/grass.png")) {
      return -1;
    }

    mtx.unlock();
    return 0;
  }
}
