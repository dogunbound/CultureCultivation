#include "mapGenerator.h"
#include "assets.h"
#include "globals.h"
#include "entities/plants/trees.h"

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <algorithm>


using namespace globals;

namespace mapGenerator {
  unsigned int mapSize = 200; // Default map size

  void mapGeneratorSwitch(const unsigned short &mapGenerationType, const int &seed) {
    switch(mapGenerationType) {
      case 0:
        mapGen_0_betaFlat(seed);
        break;
      default:
        std::cout << "undefined map generation type\n";
    }
  }

  void mapGen_0_betaFlat(const int &seed) {
    srand(seed);
    std::mutex mtx;

    mtx.lock();
    centerChunk = new MapChunk;
    centerChunk->coord = sf::Vector2i(0,0);
    mtx.unlock();

    auto loadChunkWithGrassTexture = [](MapChunk *mc) {
      for (auto r = 0; r < BlocksPerChunkAxis; r++) {
        for (auto c = 0; c < BlocksPerChunkAxis; c++) {
          auto x = mc->coord.x + r * mapSpriteSize;
          auto y = mc->coord.y + c * mapSpriteSize;
          mc->sprites[r][c] = sf::Sprite();
          sf::Sprite *sp = &mc->sprites[r][c];
          sp->setTexture(assets::spriteSheets[1]->texture);
          sp->setTextureRect(assets::spriteSheets[1]->getSpriteRectAtIndex(rand() % assets::spriteSheets[1]->numOfSprites()));
          sp->setPosition(x, y);
          sp->setScale(globals::mapSpriteSize / assets::spriteSheets[1]->sizeOfEachSprite, globals::mapSpriteSize / assets::spriteSheets[1]->sizeOfEachSprite);
        }
      }
    };

    mtx.lock();
    MapChunk *mc = centerChunk;
    loadChunkWithGrassTexture(mc);

    MapChunk *cc = mc;
    for (auto c = 0; c < mapSize; c++) {
      cc->right = new MapChunk;
      cc->right->left = cc;
      cc->right->coord = sf::Vector2i(cc->coord.x + globals::PixelsPerChunkAxis, cc->coord.y);
      cc = cc->right;
      loadChunkWithGrassTexture(cc);
    }

    MapChunk *rc = mc;
    for (auto r = 0; r < mapSize; r++) {
      rc->bottom = new MapChunk;
      rc->bottom->top = rc;
      rc->bottom->coord = sf::Vector2i(rc->coord.x, rc->coord.y + globals::PixelsPerChunkAxis);
      rc = rc->bottom;
      loadChunkWithGrassTexture(rc);

      cc = rc;
      for (auto c = 0; c < mapSize; c++) {
        // Tree generation
        int numOfTrees = rand() % 200 + 100;
        for (int i = 0; i < numOfTrees; i++) {
          cc->entities.push_back(new entity::Tree(0, sf::Vector2f(
                  rand() % globals::PixelsPerChunkAxis + cc->coord.x,
                  rand() % globals::PixelsPerChunkAxis + cc->coord.y)));
        }
        // End of tree generation
        cc->right = new MapChunk;
        cc->right->left = cc;
        cc->right->coord = sf::Vector2i(cc->coord.x + globals::PixelsPerChunkAxis, cc->coord.y);
        cc = cc->right;
        cc->top = cc->left->top->right;
        cc->top->bottom = cc;
        loadChunkWithGrassTexture(cc);
      }
    }
    mtx.unlock();
  }
}
