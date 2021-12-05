#include <iostream>
#include <cmath>

#include "assets.h"
#include "render.h"
#include "camera/camera.h"


namespace render{
  // Load Globals
  sf::Vector2f *viewMove;

  int updateFunctions() {
    int cameraUpdateSuccess = camera::updateCamera();
    if (cameraUpdateSuccess != 0 && cameraUpdateSuccess != 1) {
      std::cout << "Failed to update camera. Failed with error code: " << cameraUpdateSuccess << "\n";
      return -1;
    }

    return 0;
  }

  int render() {
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Culture & Cultivation");
    
    viewMove = new sf::Vector2f(0.0f, 0.0f);
    view = window.getDefaultView();

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
      window.display();
    }

    return 0;
  }
}
