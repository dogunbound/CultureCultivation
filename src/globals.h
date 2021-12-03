#pragma once
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <ctime>

namespace globals {
  static std::clock_t startTime;

  static sf::Font mainFont;


  static int init() {

    if (!mainFont.loadFromFile("assets/PixelFJVerdana12pt.ttf")) {
      std::cout << "Font DisposableDroidBB.ttf failed to load.\n";
      return 1;
    }
    return 0;
  }
}
