#include <iostream>
#include <thread>
#include <ctime>

#include "render/render.h"
#include "globals.h"
#include "assets.h"

// Define globals
std::clock_t globals::startTime;

int main() {
  assets::loadFonts();
  assets::loadTextures();

  globals::startTime = std::clock();
  std::thread renderThread(render::render);
  renderThread.join();
  return 0;
}
