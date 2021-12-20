#pragma once
#include "globals.h"
#include <SFML/Graphics.hpp>

namespace render {
  static sf::View worldView; // This is the world camera view
  static sf::View UIView; // This is the UI camera view
  static bool showFps = true;
  static unsigned short fps = 0; // amount of fps
  extern sf::Vector2f worldViewMove; // This is to move the camera. We can't directly access view to move it because window.setView needs to be set right after a move
  extern sf::Vector2<unsigned int> windowSize;
  extern sf::Vector2f worldViewSize;
  int render(); // This is the render method. This method is what displays and does gui processing for UI
}
