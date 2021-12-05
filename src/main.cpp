#include <iostream>
#include <thread>
#include <ctime>

#include "globals.h"
// Init globals
std::clock_t globals::startTime;
globals::MapTree globals::centerOfMap;

#include "assets.h"
// Init assets
sf::Font *assets::mainFont;
sf::Texture *assets::grass;


#include "render/render.h"


int main() {
  assets::loadFonts();
  assets::loadTextures();

  // This is where the fun really starts
  globals::startTime = std::clock();
  std::thread renderThread(render::render);
  renderThread.join();
  return 0;
}
