#include "globals.h"

#include <list>
#include <thread>
#include <mutex>

namespace world {
  static std::list<std::thread> threads;

  static void updateWorldThread(std::list<globals::MapChunk*> MapChunksToLoad) {
    std::mutex mtx;
    while (true) {
      for (auto mc : MapChunksToLoad) {
        for (auto entities : mc->entities) {
          entities->update();
        }
      }
    }
  }

  static void coreAssigner() {
    std::mutex mtx;
    mtx.lock();
    globals::MapChunk *mc = globals::centerChunk;

    while(mc->left != nullptr) {
      mc = mc->left;
    }

    while(mc->top != nullptr) {
      mc = mc->top;
    }

    globals::MapChunk *topLeftmc = mc;

    unsigned int mapSizeX = 0, mapSizeY = 0;

    while(mc->bottom != nullptr) {
      mc = mc->bottom;
      mapSizeY++;
    }

    while(mc->right != nullptr) {
      mc = mc->right;
      mapSizeX++;
    }

    mtx.unlock();

    unsigned short cores = globals::coreCount - 4;

    unsigned int numOfChunks = mapSizeX * mapSizeY;

    float chunksPerCore = numOfChunks / static_cast<float>(cores);


    unsigned short coreNum = 0;
    std::vector<std::list<globals::MapChunk*>> listOfChunksPerCore(cores);


    mtx.lock();
    globals::MapChunk *rmc = topLeftmc;
    while(rmc != nullptr) {
      globals::MapChunk *cmc = rmc;
      while(cmc != nullptr) {
        listOfChunksPerCore[coreNum].push_back(cmc);
        coreNum++;
        if (coreNum >= cores) coreNum = 0;
        cmc = cmc->right;
      }
      rmc = rmc->bottom;
    }
    mtx.unlock();

    for (auto list : listOfChunksPerCore) {
      threads.push_back(std::thread(updateWorldThread, list));
    }
  }
}
