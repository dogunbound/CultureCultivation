#include <iostream>
#include <cmath>

#include "assets.h"
#include "render.h"
#include "camera/camera.h"


namespace render{
  // Load Globals
  sf::Vector2f *viewMove; // This variable is to allow movement of the camera

  int updateFunctions() { // This is to update the camera position and other view related things
    int cameraUpdateSuccess = camera::updateCamera();
    if (cameraUpdateSuccess != 0 && cameraUpdateSuccess != 1) {
      std::cout << "Failed to update camera. Failed with error code: " << cameraUpdateSuccess << "\n";
      return -1;
    }

    return 0;
  }

  int render() { // This is where the actual rendering of the map and objects occur. No bounding just fast computation of all object images
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Culture & Cultivation");
    
    viewMove = new sf::Vector2f(0.0f, 0.0f);
    view = window.getDefaultView();
    sf::Text text;
    text.setString("Hello World!");
    text.setCharacterSize(24);
    text.setFont(*assets::mainFont);

    int c = 0;
    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
        switch (event.type) {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::Resized:
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            break;
          default:
            break;
        }

      }
      updateFunctions();
      view.move(*viewMove);
      window.setView(view);

      window.clear();
      window.draw(text);
      window.display();
    }

    return 0;
  }
}
