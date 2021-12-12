#include "assets.h"
#include "render.h"
#include "camera/camera.h"
#include "globals.h"
#include "utils/clock.h"

#include <iostream>
#include <cmath>
#include <ctime>
#include <thread>
#include <chrono>


namespace render{
  // Load Globals
  sf::Vector2f viewMove; // This variable is to allow movement of the camera
  sf::Vector2f viewSize; // Size of view port
  sf::Vector2<unsigned int> windowSize; // This variable is to figure out the size of the window. Very useful in weird ways

  int render() { // This is where the actual rendering of the map and objects occur. No bounding just fast computation of all object images
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Culture & Cultivation");
    std::mutex mtx; // our thread binder
    bool windowIsFocused = true;

    viewMove = sf::Vector2f(0.0f, 0.0f);
    view = window.getDefaultView();

    // Setup our MapChunk pointers
    mtx.lock();
    globals::MapChunk **centerChunkPointer = &globals::centerChunk; // need a double pointer to validate that center chunk is defined before printing stuff to draw
    mtx.unlock();
    globals::MapChunk *mc = nullptr; // Our actual camera view map pointer

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
              if ((view.getSize().x < 5 || view.getSize().y < 5) && event.mouseWheel.delta >= 0) { // prevent zoom from going to far in
                break;
              }
              if ((view.getSize().x > 1e5 || view.getSize().y > 1e5) && event.mouseWheel.delta < 0) { // prevent zoom from going to far out
                break;
              }
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
      mtx.lock();
      if (*centerChunkPointer != nullptr && mc == nullptr) { // init the map loader
        mc = *centerChunkPointer;
      }
      mtx.unlock();
     
      // Move view based on zoom
      view.zoom(camera::cameraZoom);
      camera::cameraZoom = 1;
      view.move(viewMove);

      // finally set the changes made onto the view onto the window
      window.setView(view);

      // With the view set, we can now make calculations on where and what coordinates need to be rendered
      sf::Vector2i viewCenter = sf::Vector2i(view.getCenter().x, view.getCenter().y);
      int xMin = viewCenter.x - view.getSize().x/2;
      int yMin = viewCenter.y - view.getSize().y/2;
      int xMax = viewCenter.x + view.getSize().x/2;
      int yMax = viewCenter.y + view.getSize().y/2;

      window.clear();
      mtx.lock();
      if (mc != nullptr) {
        int xMinChunk = xMin - xMin % globals::PixelsPerChunkAxis-globals::PixelsPerChunkAxis;
        int yMinChunk = yMin - yMin % globals::PixelsPerChunkAxis-globals::PixelsPerChunkAxis;
        std::cout << mc->coord.x << ", " << mc->coord.y << " : " << xMinChunk << ", " << yMinChunk << "\n";
        while (mc->coord.x != xMinChunk && mc->coord.y != yMinChunk) {
          if (mc->coord.x < xMinChunk && mc->right != nullptr) { // if mc coord.x is less than xMinChunk, move mc coord.x to the right
            mc = mc->right;
          }
          if (mc->coord.x < xMinChunk && mc->left != nullptr) { // if mc coord.x is greater than xMinChunk, move mc coord.y to the left
            mc = mc->left;
          }

          if (mc->coord.y < yMinChunk && mc->bottom != nullptr) { // if mc coord.y is less than yMinChunk, move mc coord.y down
            mc = mc->bottom;
          }
          if (mc->coord.y > yMinChunk && mc->top != nullptr) { // if mc coord.y is greater than yMinChunk, move mc coord.y top
            mc = mc->top;
          }
        }
        for (auto r = 0; r < globals::BlocksPerChunkAxis; r++) {
          for (auto c = 0; c < globals::BlocksPerChunkAxis; c++) {
            try {
              window.draw(mc->sprites[r][c]);
            } catch (const std::exception& e) {
              std::cout << e.what();
            }
          }
        }
      }

      int r = 5;
      sf::CircleShape circle(r);
      circle.setFillColor(sf::Color::Red);
      circle.setPosition(viewCenter.x, viewCenter.y);
      window.draw(circle);
      mtx.unlock();
      window.display();
    }

    return 0;
  }
}
