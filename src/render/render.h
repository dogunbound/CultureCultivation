#pragma once
#include <SFML/Graphics.hpp>
#include "globals.h"

namespace render {
  static sf::View view;
  extern sf::Vector2f *viewMove;
  int render();
}
