#pragma once
#include <SFML/Graphics.hpp>
#include "globals.h"

namespace render {
  static sf::View view; // This is the camera view
  extern sf::Vector2f *viewMove; // This is to move the camera. We can't directly access view to move it because window.setView needs to be set right after a move
  int render(); // This is the render method. This method is what displays and does gui processing for UI
}
