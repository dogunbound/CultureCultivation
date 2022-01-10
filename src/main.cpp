#include "globals.h"
#include "assets.h"
#include "render/render.h"
#include "mapGeneration/mapGenerator.h"
#include "utils/assetClasses.h"
#include "world/worldUpdater.h"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <thread>
#include <ctime>

// Init globals
std::clock_t globals::startTime;
globals::MapChunk* globals::centerChunk;
unsigned short globals::coreCount;
static int globals::init();
// Init assets
sf::Font *assets::mainFont;
assets::SpriteSheet *assets::spriteSheets[3];



int main() {
  // Hardcode corecount
  globals::coreCount = 16;
  globals::init();
  assets::loadFonts();
  assets::loadTextures();

  // This is where the fun really starts
  globals::startTime = std::clock();
  std::thread renderThread(render::render);
  std::thread mapGeneratorThread(mapGenerator::mapGeneratorSwitch, 0, 0);

  mapGeneratorThread.join();
  world::coreAssigner();
  renderThread.join();
  return 0;
}
