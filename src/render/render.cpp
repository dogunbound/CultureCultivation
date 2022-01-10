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
  sf::Vector2f worldViewMove; // This variable is to allow movement of the camera
  sf::Vector2f worldViewSize; // Size of worldView port
  sf::Vector2<unsigned int> windowSize; // This variable is to figure out the size of the window. Very useful in weird ways

  int render() { // This is where the actual rendering of the map and objects occur. No bounding just fast computation of all object images
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Culture & Cultivation");
    std::mutex mtx; // our thread binder
    bool windowIsFocused = true;

    worldViewMove = sf::Vector2f(0.0f, 0.0f);
    worldView = window.getDefaultView();
    UIView = window.getDefaultView();

    // Setup our MapChunk pointers
    mtx.lock();
    globals::MapChunk **centerChunkPointer = &globals::centerChunk; // need a double pointer to validate that center chunk is defined before printing stuff to draw
    mtx.unlock();
    globals::MapChunk *mc = nullptr; // Our actual camera view map pointer

    // Get fps
    unsigned short frameCount = 0;
    std::clock_t lastSecond = std::clock();
    sf::Text fpsCounter;
    fpsCounter.setFont(*assets::mainFont);
    fpsCounter.setCharacterSize(16);

    int c = 0;
    std::clock_t timeOfLastRender = std::clock(); // This is to setup the timer that forces c++ to stop rendering for a little bit and ease up
    
    while (window.isOpen()) {
      // Calculate fps
      frameCount++;
      std::clock_t diffFromLastSecond = std::clock() - lastSecond;
      if (diffFromLastSecond > CLOCKS_PER_SEC) {
        fps = frameCount;
        frameCount = 0;
        lastSecond = std::clock();
      }
      // END Calculate fps
      

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
              if ((worldView.getSize().x < 5 || worldView.getSize().y < 5) && event.mouseWheel.delta >= 0) { // prevent zoom from going to far in
                break;
              }
              if ((worldView.getSize().x > 1e5 || worldView.getSize().y > 1e5) && event.mouseWheel.delta < 0) { // prevent zoom from going to far out
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
            worldView.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
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
      // Setup window and worldView sizing each frame
      // MUST be done before update
      windowSize = sf::Vector2<unsigned int>(window.getSize().x, window.getSize().y);
      worldViewSize = sf::Vector2f(worldView.getSize().x, worldView.getSize().y);
      mtx.lock();
      if (*centerChunkPointer != nullptr && mc == nullptr) { // init the map loader
        mc = *centerChunkPointer;
      }
      mtx.unlock();
     
      // Move worldView based on zoom
      worldView.zoom(camera::cameraZoom);
      camera::cameraZoom = 1;
      worldView.move(worldViewMove);

      // finally set the changes made onto the worldView onto the window
      window.setView(worldView);

      // With the worldView set, we can now make calculations on where and what coordinates need to be rendered
      sf::Vector2i worldViewCenter = sf::Vector2i(worldView.getCenter().x, worldView.getCenter().y);
      int xMin = worldViewCenter.x - worldView.getSize().x/2 - globals::PixelsPerChunkAxis;
      int yMin = worldViewCenter.y - worldView.getSize().y/2 - globals::PixelsPerChunkAxis;
      int xMax = worldViewCenter.x + worldView.getSize().x/2 + 2*globals::PixelsPerChunkAxis;
      int yMax = worldViewCenter.y + worldView.getSize().y/2 + 2*globals::PixelsPerChunkAxis;

      window.clear();
      if (mc != nullptr) {
        int xMinChunk = xMin - xMin % globals::PixelsPerChunkAxis;
        int yMinChunk = yMin - yMin % globals::PixelsPerChunkAxis;
        while (mc->coord.y > yMin && mc->top != nullptr) { // Move up to find the proper y position to start render at
          mc = mc->top;
        }
        while (mc->coord.y < yMin && mc->bottom != nullptr) { // Move down to the proper y position
          mc = mc->bottom;
        }
        while (mc->coord.x > xMin && mc->left != nullptr) { // Move left to the proper x position
          mc = mc->left;
        }
        while (mc->coord.x < xMin && mc->right != nullptr) { // Move right to the proper x position
          mc = mc->right;
        }

        globals::MapChunk *rowmc = mc;
        while (rowmc->bottom != nullptr && rowmc->bottom->coord.y < yMax) {
          globals::MapChunk *colmc = rowmc;
          while (colmc->right != nullptr && colmc->right->coord.x < xMax) {
            for (auto r = 0; r < globals::BlocksPerChunkAxis; r++) {
              for (auto c = 0; c < globals::BlocksPerChunkAxis; c++) {
                try {
                  window.draw(colmc->sprites[r][c]);
                } catch (const std::exception& e) {
                  std::cout << e.what();
                }
              }
            }
            colmc = colmc->right;
          }
          rowmc = rowmc->bottom;
        }

        rowmc = mc;
        while (rowmc->bottom != nullptr && rowmc->bottom->coord.y < yMax) {
          globals::MapChunk *colmc = rowmc;
          while (colmc->right != nullptr && colmc->right->coord.x < xMax) {
            for (auto entity : colmc->entities) {
              window.draw(entity->getSprite());
            }
            colmc = colmc->right;
          }
          rowmc = rowmc->bottom;
        }
      }

      sf::Vector2i UIViewCenter = sf::Vector2i(UIView.getCenter().x, UIView.getCenter().y);
      int UIxMin = UIViewCenter.x - UIView.getSize().x/2;
      int UIyMin = UIViewCenter.y - UIView.getSize().y/2;
      int UIxMax = UIViewCenter.x + UIView.getSize().x/2;
      int UIyMax = UIViewCenter.y + UIView.getSize().y/2;

      UIView = sf::View(sf::FloatRect(0,0,window.getSize().x, window.getSize().y));
      window.setView(UIView);
      // Fps draw
      if (showFps) {
        fpsCounter.setString(std::to_string(fps));
        fpsCounter.setPosition(UIxMax - fpsCounter.getLocalBounds().width-5, UIyMin + fpsCounter.getLocalBounds().height-10);
        window.draw(fpsCounter);
      }
      window.display();

      // World view
    }

    return 0;
  }
}
