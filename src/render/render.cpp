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
        switch (event.type) {
          case sf::Event::Closed:
            window.close();
            break;
          case sf::Event::Resized:
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            break;
          case sf::Event::MouseWheelMoved:
            camera::cameraZoom *= (event.mouseWheel.delta >= 0) ? 0.75d : 1.5;
            break;
          default:
            break;
        }

      }
      // Setup window and view sizing each frame
      // MUST be done before update
      windowSize = sf::Vector2<unsigned int>(window.getSize().x, window.getSize().y);
      viewSize = sf::Vector2f(view.getSize().x, view.getSize().y);

      updateFunctions();
      view.zoom(camera::cameraZoom);
      camera::cameraZoom = 1;
      view.move(viewMove);
      window.setView(view);

      window.clear();
      mtx.lock();
      if (globals::centerChunk != nullptr) {
        globals::MapChunk *mc = *&globals::centerChunk;
        do {
          for (unsigned char r = 0; r < globals::chunkSize; r++) {
            for (unsigned char c = 0; c < globals::chunkSize; c++) {
              //std::cout << *&mc->sprites[r][c].getPosition().x << " " << *&mc->sprites[r][c].getPosition().y << "\n";
              window.draw(*&mc->sprites[r][c]);
            }
          }
          mc = *&mc->up;
        } while (mc != nullptr);
      }
      mtx.unlock();
      window.display();
    }

    return 0;
  }
}
