#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <thread>

#include "mapGenerator.h"
#include "assets.h"
#include "globals.h"

namespace mapGenerator {

  int mapGeneratorSwitch(const unsigned short &mapGenerationType, const int &seed) {
    switch(mapGenerationType) {
      case 0:
        mapGen_0_betaFlat(seed);
        break;
      default:
        std::cout << "undefined map generation type\n";
        return 1; // Undefined mapGenerationType.
    }

    return 0; // Pass
  }

  int mapGen_0_betaFlat(const int &seed) {
    srand(seed);
    std::mutex mtx;

    mtx.lock();
    globals::centerChunk = new globals::MapChunk;
    globals::centerChunk->coord = sf::Vector2i(0,0);
    mtx.unlock();

    auto setGrassSpriteIndexPos = [](globals::MapChunk *mc, unsigned short r, unsigned short c, int x, int y) {
      mc->sprites[r][c] = sf::Sprite();
      sf::Sprite *sp = &globals::centerChunk->sprites[r][c];
      sp->setTexture(*assets::grass);
      sp->setPosition(x, y);
      sp->setScale(2,2);
    };

    /*
    // load center chunk. The next chunks being loaded is where the real fun begins
    for ( unsigned short r = 0; r < globals::chunkSize; r++) {
      for ( unsigned short c = 0; c < globals::chunkSize; c++) {
        mtx.lock();
        setGrassSpriteIndexPos(*&globals::centerChunk, r, c, r * globals::mapSpriteSize, c * globals::mapSpriteSize);
        mtx.unlock();
      }
    }*/

    mtx.lock();
    globals::MapChunk *mc = *&globals::centerChunk;
    mtx.unlock();
    for (unsigned int i = 0; i < 20; i++) {
      // up
      for (unsigned short r = 0; r < globals::chunkSize; r++) {
        for (unsigned short c = 0; c < globals::chunkSize; c++) {
          mtx.lock();
          setGrassSpriteIndexPos(*&mc, r, c, mc->coord.x + r * globals::mapSpriteSize, mc->coord.y - c * globals::mapSpriteSize);
          mtx.unlock();
        }
      }

      mtx.lock();
      mc->up = new globals::MapChunk;
      globals::MapChunk *tmp = *&mc;
      mc = *&mc->up;
      mc->down = *&tmp;
      mc->coord = sf::Vector2i(tmp->coord.x, tmp->coord.y - globals::chunkSize * globals::mapSpriteSize);
      mtx.unlock();
    }
    return 0; // Pass
  }
}
