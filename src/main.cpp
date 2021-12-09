#include <iostream>
#include <thread>
#include <ctime>

#include "globals.h"
// Init globals
std::clock_t globals::startTime;
globals::MapChunk* globals::centerChunk;
unsigned short coreCount;
globals::EntityTree *globals::eTree;
static int globals::init();

#include "assets.h"
// Init assets
sf::Font *assets::mainFont;
sf::Texture *assets::grass;


#include "render/render.h"
#include "mapGeneration/mapGenerator.h"


int main() {
  // Hardcode corecount
  coreCount = 16;
  globals::init();
  assets::loadFonts();
  assets::loadTextures();

  // This is where the fun really starts
  globals::startTime = std::clock();
  std::thread mapGeneratorThread(mapGenerator::mapGeneratorSwitch, 0, 0);
  std::thread renderThread(render::render);

  renderThread.join();
  mapGeneratorThread.join();
  return 0;
}
