#include "mapGenerator.h"
#include "assets.h"
#include "globals.h"

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <thread>
#include <list>
#include <algorithm>


using namespace globals;

namespace mapGenerator {

  // Must be done AFTER centerchunk is established
  int testMapGenCoordinates(MapChunk *mc, std::list<sf::Vector2i> &finishedCoords) {
    sf::Vector2i tmpVector2i;
    std::mutex mtx;

    mtx.lock();
    tmpVector2i = mc->coord;
    mtx.unlock();
    std::list<sf::Vector2i>::iterator find = std::find(finishedCoords.begin(), finishedCoords.end(), tmpVector2i);

    if (find == finishedCoords.end()) {
      return 0;
    }

    mtx.lock();
    // Left
    tmpVector2i = mc->left->coord;
    if (mc->coord.x != tmpVector2i.x + PixelsPerChunkAxis) {
      std::cout << "Map chunk " << mc << " has non-corresponding x coordinate with it's left partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->left coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
    if (mc->coord.y != tmpVector2i.y) {
      std::cout << "Map chunk " << mc << " has non-corresponding x coordinate with it's left partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->left coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }

    // Right
    tmpVector2i = mc->right->coord;
    if (mc->coord.x != tmpVector2i.x - PixelsPerChunkAxis) { 
      std::cout << "Map chunk " << mc << " has non-corresponding x coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
    if (mc->coord.y != tmpVector2i.y) { 
      std::cout << "Map chunk " << mc << " has non-corresponding y coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
   
    // Top
    tmpVector2i = mc->top->coord;
    if (mc->coord.x != tmpVector2i.x) { 
      std::cout << "Map chunk " << mc << " has non-corresponding x coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
    if (mc->coord.y != tmpVector2i.y + PixelsPerChunkAxis) { 
      std::cout << "Map chunk " << mc << " has non-corresponding y coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
    
    // bottom
    tmpVector2i = mc->bottom->coord;
    if (mc->coord.x != tmpVector2i.x) { 
      std::cout << "Map chunk " << mc << " has non-corresponding x coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }
    if (mc->coord.y != tmpVector2i.y - PixelsPerChunkAxis) { 
      std::cout << "Map chunk " << mc << " has non-corresponding y coordinate with it's right partner. mc coord: " << mc->coord.x << ", " << mc->coord.y << " mc->right coord: " << tmpVector2i.x << ", " << tmpVector2i.y << "\n";
      return 1;
    }

    if (mc->top != nullptr) {
      return testMapGenCoordinates(mc->top, finishedCoords);
    }
    if (mc->bottom != nullptr) { 
      return testMapGenCoordinates(mc->bottom, finishedCoords);
    }
    if (mc->right != nullptr) {
      return testMapGenCoordinates(mc->right, finishedCoords);
    }
    if (mc->left != nullptr) { 
      return testMapGenCoordinates(mc->left, finishedCoords);
    }
    mtx.unlock();
    return 0;
  }

  int mapGeneratorSwitch(const unsigned short &mapGenerationType, const int &seed) {
    switch(mapGenerationType) {
      case 0:
        mapGen_0_betaFlat(seed);
        break;
      default:
        std::cout << "undefined map generation type\n";
        return 1; // Undefined mapGenerationType.
    }

    if (false) { // tests
      std::list<sf::Vector2i> finishedCoords;
      if (testMapGenCoordinates(centerChunk, finishedCoords) != 0) {
        std::cout << "map generation .................... failed\n";
      } else {
        std::cout << "map generation .................... passed\n";
      }
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
      for (auto r = 0; r < BlocksPerChunkAxis; r++) {
        for (auto c = 0; c < BlocksPerChunkAxis; c++) {
          mtx.lock();
          auto x = mc->coord.x + r * mapSpriteSize;
          auto y = mc->coord.y + c * mapSpriteSize;
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
    loadChunkWithGrassTexture(mc);
    mtx.unlock();

    unsigned int chunksOutCount = 0;
    while (chunksOutCount < 50) {
      mtx.lock();
      // Just a tmp variable to make the code easier to look at and debug
      sf::Vector2i tmpVector2i;
      // First move the chunk that will be loaded out one in all directions and setup the coordinates
      // Left side out
      leftSide->left = new MapChunk;
      leftSide->left->right = leftSide;
      leftSide = leftSide->left;
      tmpVector2i = leftSide->right->coord;
      leftSide->coord = sf::Vector2i(tmpVector2i.x-PixelsPerChunkAxis, tmpVector2i.y);
      // Right side out
      rightSide->right = new MapChunk;
      rightSide->right->left = rightSide;
      rightSide = rightSide->right;
      tmpVector2i = rightSide->left->coord;
      rightSide->coord = sf::Vector2i(tmpVector2i.x+PixelsPerChunkAxis, tmpVector2i.y);
      // Top side out
      topSide->top = new MapChunk;
      topSide->top->bottom = topSide;
      topSide = topSide->top;
      tmpVector2i = topSide->bottom->coord;
      topSide->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y-PixelsPerChunkAxis);
      // Bottom side out
      bottomSide->bottom = new MapChunk;
      bottomSide->bottom->top = bottomSide;
      bottomSide = bottomSide->bottom;
      tmpVector2i = bottomSide->top->coord;
      bottomSide->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y+PixelsPerChunkAxis);

      // Load the grass texture to all the above components
      loadChunkWithGrassTexture(leftSide);
      loadChunkWithGrassTexture(rightSide);
      loadChunkWithGrassTexture(bottomSide);
      loadChunkWithGrassTexture(topSide);
      
      // We first moved the middle of the chunks out.
      // Next, we need to move the sides outwards and fill it up to the corners
      MapChunk *topSideLeft = topSide; // top side that goes left
      MapChunk *topSideRight = topSide; // top side that goes right
      MapChunk *bottomSideLeft = bottomSide; // bottom side that goes left
      MapChunk *bottomSideRight = bottomSide; // bottom side that goes right
      MapChunk *rightSideTop = rightSide; // right side that goes up
      MapChunk *rightSideBottom = rightSide; // right side that goes down
      MapChunk *leftSideTop = leftSide; // left side that goes up
      MapChunk *leftSideBottom = leftSide; // left side that goes down
      for (auto i = 0; i < chunksOutCount; i++) {
        // Move the topSideLeft point to the topLeft corner
        topSideLeft->left = new MapChunk;
        topSideLeft->left->right = topSideLeft;
        topSideLeft->left->bottom = topSideLeft->bottom->left;
        topSideLeft->bottom->left->top = topSideLeft->left;
        topSideLeft = topSideLeft->left;
        tmpVector2i = topSideLeft->right->coord;
        topSideLeft->coord = sf::Vector2i(tmpVector2i.x-PixelsPerChunkAxis, tmpVector2i.y);
        // Move the topSideRight point to the topRight corner
        topSideRight->right = new MapChunk;
        topSideRight->right->left = topSideRight;
        topSideRight->right->bottom = topSideRight->bottom->right;
        topSideRight->bottom->right = topSideRight->right;
        topSideRight = topSideRight->right;
        tmpVector2i = topSideRight->left->coord;
        topSideRight->coord = sf::Vector2i(tmpVector2i.x+PixelsPerChunkAxis, tmpVector2i.y);
        // Move the bottomSideLeft point to the bottomLeft corner
        bottomSideLeft->left = new MapChunk;
        bottomSideLeft->left->right = bottomSideLeft;
        bottomSideLeft->left->top = bottomSideLeft->top->left;
        bottomSideLeft->top->left->bottom = bottomSideLeft->left;
        bottomSideLeft = bottomSideLeft->left;
        tmpVector2i = bottomSideLeft->right->coord;
        bottomSideLeft->coord = sf::Vector2i(tmpVector2i.x-PixelsPerChunkAxis, tmpVector2i.y);
        // Move the bottomSideRight point to the bottomRight corner
        bottomSideRight->right = new MapChunk;
        bottomSideRight->right->left = topSideRight;
        bottomSideRight->right->top = bottomSideRight->top->right;
        bottomSideRight->top->right = bottomSideRight->right;
        bottomSideRight = bottomSideRight->right;
        tmpVector2i = bottomSideRight->left->coord;
        bottomSideRight->coord = sf::Vector2i(tmpVector2i.x+PixelsPerChunkAxis, tmpVector2i.y);
        // Move the rightSideTop point to the topRight corner
        rightSideTop->top = new MapChunk;
        rightSideTop->top->bottom = rightSideTop;
        rightSideTop->top->left = rightSideTop->left->top;
        rightSideTop->left->top->right = rightSideTop->top;
        rightSideTop = rightSideTop->top;
        tmpVector2i = rightSideTop->bottom->coord;
        rightSideTop->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y-PixelsPerChunkAxis);
        // Move the rightSideBottom point to the bottomRight corner
        rightSideBottom->bottom = new MapChunk;
        rightSideBottom->bottom->top = rightSideBottom;
        rightSideBottom->bottom->left = rightSideBottom->left->bottom;
        rightSideBottom->left->bottom->right = rightSideBottom->bottom;
        rightSideBottom = rightSideBottom->bottom;
        tmpVector2i = rightSideBottom->top->coord;
        rightSideBottom->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y+PixelsPerChunkAxis);
        // Move the rightSideTop point to the topRight corner
        leftSideTop->top = new MapChunk;
        leftSideTop->top->bottom = leftSideTop;
        leftSideTop->top->right = leftSideTop->right->top;
        leftSideTop->right->top->left = leftSideTop->top;
        leftSideTop = leftSideTop->top;
        tmpVector2i = leftSideTop->bottom->coord;
        leftSideTop->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y-PixelsPerChunkAxis);
        // Move the rightSideBottom point to the bottomRight corner
        leftSideBottom->bottom = new MapChunk;
        leftSideBottom->bottom->top = leftSideBottom;
        leftSideBottom->bottom->right = leftSideBottom->right->bottom;
        leftSideBottom->right->bottom->left = leftSideBottom->bottom;
        leftSideBottom = leftSideBottom->bottom;
        tmpVector2i = leftSideBottom->top->coord;
        leftSideBottom->coord = sf::Vector2i(tmpVector2i.x, tmpVector2i.y+PixelsPerChunkAxis);
        
        // Render EVERY chunk with sprites. This is the haevy task lol
        loadChunkWithGrassTexture(topSideLeft);
        loadChunkWithGrassTexture(topSideRight);
        loadChunkWithGrassTexture(bottomSideLeft);
        loadChunkWithGrassTexture(bottomSideRight);
        loadChunkWithGrassTexture(leftSideTop);
        loadChunkWithGrassTexture(leftSideBottom);
        loadChunkWithGrassTexture(rightSideTop);
        loadChunkWithGrassTexture(rightSideBottom);
      }

      // Now to initialize the corners of this next outward section
      // top left corner
      topSideLeft->left = new MapChunk;
      topSideLeft->left->right = topSideLeft;
      topSideLeft = topSideLeft->left;
      leftSideTop->top = topSideLeft;
      topSideLeft->bottom = rightSideTop;
      leftSideTop = topSideLeft;
      // top right corner
      topSideRight->right = new MapChunk;
      topSideRight->right->left = topSideRight;
      topSideRight = topSideRight->right;
      rightSideTop->top = topSideRight;
      topSideRight->bottom = rightSideTop;
      rightSideTop = topSideRight;
      // bottom left corner
      bottomSideLeft->left = new MapChunk;
      bottomSideLeft->left->right = bottomSideLeft;
      bottomSideLeft = bottomSideLeft->left;
      bottomSideLeft->top = leftSideBottom;
      leftSideBottom->bottom = bottomSideLeft;
      leftSideBottom = bottomSideLeft;
      // bottom right corner
      bottomSideRight->right = new MapChunk;
      bottomSideRight->right->left = bottomSideRight;
      bottomSideRight = bottomSideRight->right;
      rightSideBottom->bottom = bottomSideRight;
      bottomSideRight->top = rightSideBottom;
      rightSideBottom = bottomSideRight;
      
      // Assigning coordinates to each corner chunk
      tmpVector2i = topSideLeft->right->coord;
      topSideLeft->coord = sf::Vector2i(tmpVector2i.x-PixelsPerChunkAxis, tmpVector2i.y);
      tmpVector2i = topSideRight->left->coord;
      topSideRight->coord = sf::Vector2i(tmpVector2i.x+PixelsPerChunkAxis, tmpVector2i.y);
      tmpVector2i = bottomSideLeft->right->coord;
      bottomSideLeft->coord = sf::Vector2i(tmpVector2i.x-PixelsPerChunkAxis, tmpVector2i.y);
      tmpVector2i = bottomSideRight->left->coord;
      bottomSideRight->coord = sf::Vector2i(tmpVector2i.x+PixelsPerChunkAxis, tmpVector2i.y);
      
      chunksOutCount++;
      mtx.unlock();
    }
    return 0; // Pass
  }
}
