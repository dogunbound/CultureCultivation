#include <iostream>
#include <cmath>
#include <ctime>
#include <thread>
#include <chrono>

#include "assets.h"
#include "render.h"
#include "camera/camera.h"
#include "globals.h"
#include "utils/clock.h"


namespace render{
  // Load Globals
  sf::Vector2f viewMove; // This variable is to allow movement of the camera
  sf::Vector2f viewSize; // Size of view port
  sf::Vector2<unsigned int> windowSize; // This variable is to figure out the size of the window. Very useful in weird ways

  int render() { // This is where the actual rendering of the map and objects occur. No bounding just fast computation of all object images
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Culture & Cultivation");
    bool windowIsFocused = true;

    viewMove = sf::Vector2f(0.0f, 0.0f);
    view = window.getDefaultView();

    std::mutex mtx; // our thread binder
    int c = 0;
    std::clock_t timeOfLastRender = std::clock(); // This is to setup the timer that forces c++ to stop rendering for a little bit and ease up
    while (window.isOpen())
    {
      if (utils::ctimeToMilliseconds((abs(timeOfLastRender - std::clock()))) < 7) { // this basically allows for 150 frames / second, no more.
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(utils::ctimeToMilliseconds((abs(7 - (timeOfLastRender - std::clock())))))));
      }
      timeOfLastRender = std::clock(); // update time once sleep is finished
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (windowIsFocused) { // Only register inputs if window is focused
          switch (event.type) {
            case sf::Event::MouseWheelMoved:
              camera::cameraZoom *= (event.mouseWheel.delta >= 0) ? 0.75d : 1.5;
              break;
            default:
              break;
          }
        }

        switch (event.type) {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::Resized:
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            break;
          case sf::Event::GainedFocus:
            windowIsFocused = true;
            break;
          case sf::Event::LostFocus:
            windowIsFocused = false;
            break;
          default:
            break;
        }

      }

      if (windowIsFocused) { // Only register inputs if window is focused
        camera::updateCamera();
      }
      // Setup window and view sizing each frame
      // MUST be done before update
      windowSize = sf::Vector2<unsigned int>(window.getSize().x, window.getSize().y);
      viewSize = sf::Vector2f(view.getSize().x, view.getSize().y);
      
      view.zoom(camera::cameraZoom);
      camera::cameraZoom = 1;
      view.move(viewMove);
      window.setView(view);

      window.clear();
      mtx.lock();
      if (globals::centerChunk != nullptr) {
        globals::MapChunk *mc = *&globals::centerChunk;
      }
      mtx.unlock();
      window.display();
    }

    return 0;
  }
}
