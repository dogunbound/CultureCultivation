#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <thread>

#include "mapGenerator.h"
#include "assets.h"
#include "globals.h"

using namespace globals;

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
    centerChunk = new MapChunk;
    centerChunk->coord = sf::Vector2i(0,0);
    mtx.unlock();

    auto loadChunkWithGrassTexture = [](MapChunk *mc) {
      std::mutex mtx;
      for (unsigned short r = 0; r < BlocksPerChunkAxis; r++) {
        for (unsigned short c = 0; c < BlocksPerChunkAxis; c++) {
          mtx.lock();
          int x = mc->coord.x + r * mapSpriteSize;
          int y = mc->coord.y - c * mapSpriteSize;
          mc->sprites[r][c] = sf::Sprite();
          sf::Sprite *sp = &mc->sprites[r][c];
          sp->setTexture(*assets::grass);
          sp->setPosition(x, y);
          sp->setScale(2,2);
          mtx.unlock();
        }
      }
    };

    mtx.lock();
    MapChunk *mc = centerChunk;
    MapChunk *leftSide = centerChunk;
    MapChunk *rightSide = centerChunk;
    MapChunk *topSide = centerChunk;
    MapChunk *bottomSide = centerChunk;
    mtx.unlock();

    bool finished = false;
    while (!finished) {
      mtx.lock();
      // find corner of each new step up
      MapChunk *topLeft = topSide;
      MapChunk *topRight = topSide;
      MapChunk *bottomLeft = bottomSide;
      MapChunk *bottomRight = bottomSide;
      while (topLeft->left != nullptr) {
        topLeft = topLeft->left;
        topRight = topRight->right;
        bottomLeft = bottomLeft->left;
        bottomRight = bottomRight->right;
      }

      // initialize new corner
      topLeft->topLeft = new MapChunk;
      topRight->topRight = new MapChunk;
      bottomLeft->bottomLeft = new MapChunk;
      bottomRight->bottomRight = new MapChunk;
      topLeft->topLeft->bottomRight = topLeft;
      topRight->topRight->bottomLeft = topRight;
      bottomLeft->bottomLeft->topRight = bottomLeft;
      bottomRight->bottomRight->topLeft = bottomRight;

      // Fill row between topLeft-topRight, bottomLeft-bottomRight, and fill column between topLeft-bottomLeft and topRight-bottomRight
      MapChunk *fillTop = topLeft->topLeft;
      MapChunk *fillBottom = bottomLeft->bottomLeft;
      MapChunk *fillLeft = topLeft->topLeft;
      MapChunk *fillRight = topRight->topRight;
      while (topLeft->left != topRight) {
      }

      // Move sides outwards
      rightSide = rightSide->right;
      leftSide = leftSide->left;
      topSide = topSide->top;
      bottomSide = bottomSide->bottom;
      mtx.unlock();
    }
    return 0; // Pass
  }
}
