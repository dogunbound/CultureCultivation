#include "globals.h"
#include "assets.h"
#include "render/render.h"
#include "mapGeneration/mapGenerator.h"
#include "utils/assetClasses.h"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <thread>
#include <ctime>

// Init globals
std::clock_t globals::startTime;
globals::MapChunk* globals::centerChunk;
unsigned short globals::coreCount;
globals::EntityTree *globals::eTree;
static int globals::init();
// Init assets
sf::Font *assets::mainFont;
sf::Texture *assets::grass;
assets::SpriteSheet *assets::autumnGrass;



int main() {
  // Hardcode corecount
  globals::coreCount = 16;
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
