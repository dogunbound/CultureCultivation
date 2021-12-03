#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "render.h"

namespace render{
  int render() {
    sf::RenderWindow window(sf::VideoMode(1024, 576), "SFML works!");

    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
      }

      window.clear();
      sf::Text text;
      text.setFont(globals::mainFont);
      text.setString("Hello world!");
      text.setFillColor(sf::Color::White);
      text.setPosition(50, 50);
      window.draw(text);
      window.display();
    }

    return 0;
  }
}
